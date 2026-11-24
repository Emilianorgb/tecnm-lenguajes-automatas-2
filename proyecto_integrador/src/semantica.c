
/* semantica.c - Analizador semantico de Lenguajito. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compilador.h"

#define MAX_VARIABLES 256
#define MAX_NOMBRE 128

/* Informacion de una variable. */
typedef struct {
    char nombre[MAX_NOMBRE];
    int inicializada;
} Simbolo;

/* Tabla de simbolos de cada ambito. */
typedef struct Ambito {
    Simbolo simbolos[MAX_VARIABLES];
    int cantidad;
    struct Ambito* padre;
} Ambito;

/* Crear un nuevo ambito. */
static Ambito* crear_ambito(Ambito* padre) {
    Ambito* nuevo = calloc(1, sizeof(Ambito));

    if (nuevo == NULL) {
        return NULL;
    }

    nuevo->padre = padre;
    return nuevo;
}

/* Buscar una variable en el ambito actual. */
static Simbolo* buscar_local(
    Ambito* ambito,
    const char* nombre
) {
    for (int i = 0; i < ambito->cantidad; i++) {
        if (strcmp(ambito->simbolos[i].nombre, nombre) == 0) {
            return &ambito->simbolos[i];
        }
    }

    return NULL;
}

/* Buscar una variable en el ambito actual y sus padres. */
static Simbolo* buscar_variable(
    Ambito* ambito,
    const char* nombre
) {
    while (ambito != NULL) {
        Simbolo* simbolo = buscar_local(ambito, nombre);

        if (simbolo != NULL) {
            return simbolo;
        }

        ambito = ambito->padre;
    }

    return NULL;
}

/* Registrar una variable en el ambito actual. */
static int declarar_variable(
    Ambito* ambito,
    const char* nombre,
    int inicializada
) {
    if (ambito->cantidad >= MAX_VARIABLES) {
        return 0;
    }

    Simbolo* nuevo = &ambito->simbolos[ambito->cantidad];

    snprintf(
        nuevo->nombre,
        sizeof(nuevo->nombre),
        "%s",
        nombre
    );

    nuevo->inicializada = inicializada;
    ambito->cantidad++;

    return 1;
}

/* Copia del estado de inicializacion de los ambitos. */
typedef struct EstadoAmbito {
    Ambito* ambito;
    int cantidad;
    int inicializada[MAX_VARIABLES];
    struct EstadoAmbito* padre;
} EstadoAmbito;

/* Guardar el estado actual de un ambito y sus padres. */
static EstadoAmbito* guardar_estado(Ambito* ambito) {
    if (ambito == NULL) {
        return NULL;
    }

    EstadoAmbito* estado = calloc(1, sizeof(EstadoAmbito));

    if (estado == NULL) {
        return NULL;
    }

    estado->ambito = ambito;
    estado->cantidad = ambito->cantidad;

    for (int i = 0; i < ambito->cantidad; i++) {
        estado->inicializada[i] =
            ambito->simbolos[i].inicializada;
    }

    if (ambito->padre != NULL) {
        estado->padre = guardar_estado(ambito->padre);

        if (estado->padre == NULL) {
            free(estado);
            return NULL;
        }
    }

    return estado;
}

/* Restaurar el estado de inicializacion guardado. */
static void restaurar_estado(const EstadoAmbito* estado) {
    if (estado == NULL) {
        return;
    }

    for (int i = 0; i < estado->cantidad; i++) {
        estado->ambito->simbolos[i].inicializada =
            estado->inicializada[i];
    }

    restaurar_estado(estado->padre);
}

/* Combinar dos ramas: solo conservar inicializaciones comunes. */
static void combinar_estados(
    Ambito* ambito,
    const EstadoAmbito* rama_si,
    const EstadoAmbito* rama_no
) {
    if (ambito == NULL || rama_si == NULL || rama_no == NULL) {
        return;
    }

    for (int i = 0; i < ambito->cantidad; i++) {
        ambito->simbolos[i].inicializada =
            rama_si->inicializada[i] &&
            rama_no->inicializada[i];
    }

    combinar_estados(
        ambito->padre,
        rama_si->padre,
        rama_no->padre
    );
}

/* Liberar una copia del estado. */
static void liberar_estado(EstadoAmbito* estado) {
    if (estado == NULL) {
        return;
    }

    liberar_estado(estado->padre);
    free(estado);
}

/* Revisar las variables utilizadas en una expresion. */
static int revisar_expresion(
    const AST* nodo,
    Ambito* ambito,
    const char* ruta
) {
    if (nodo == NULL) {
        return 0;
    }

    int errores = 0;

    /* Detectar division entre cero cuando el divisor es constante. */
    if (nodo->tipo == AST_BINARIA &&
        nodo->valor != NULL &&
        strcmp(nodo->valor, "/") == 0 &&
        nodo->derecha != NULL &&
        nodo->derecha->tipo == AST_NUM &&
        nodo->derecha->valor != NULL &&
        strtol(nodo->derecha->valor, NULL, 10) == 0) {

        fprintf(
            stdout,
            "%s:%d:%d: error E04: division entre cero\n",
            ruta,
            nodo->linea,
            nodo->columna
        );

        errores++;
    }

    if (nodo->tipo == AST_VAR) {
        Simbolo* simbolo = buscar_variable(
            ambito,
            nodo->valor
        );

        if (simbolo == NULL) {
            fprintf(
                stdout,
                "%s:%d:%d: error E01: variable '%s' no declarada\n",
                ruta,
                nodo->linea,
                nodo->columna,
                nodo->valor
            );

            errores++;
        }
        else if (!simbolo->inicializada) {
            fprintf(
                stdout,
                "%s:%d:%d: error E01: variable '%s' sin valor\n",
                ruta,
                nodo->linea,
                nodo->columna,
                nodo->valor
            );

            errores++;
        }
    }

    errores += revisar_expresion(
        nodo->izquierda,
        ambito,
        ruta
    );

    errores += revisar_expresion(
        nodo->derecha,
        ambito,
        ruta
    );

    return errores;
}

/* Declaracion anticipada de revisar_nodo. */
static int revisar_nodo(
    const AST* nodo,
    Ambito* ambito,
    const char* ruta
);
/* Revisar las instrucciones de un bloque. */
static int revisar_bloque(
    const AST* nodo,
    Ambito* padre,
    const char* ruta
) {
    Ambito* local = crear_ambito(padre);

    if (local == NULL) {
        fprintf(stderr, "Error: no se pudo crear un ambito.\n");
        return 1;
    }

    int errores = 0;

    for (size_t i = 0; i < nodo->cantidad_hijos; i++) {
        errores += revisar_nodo(
            nodo->hijos[i],
            local,
            ruta
        );
    }

    free(local);

    return errores;
}

/* Revisar las instrucciones del programa. */
static int revisar_nodo(
    const AST* nodo,
    Ambito* ambito,
    const char* ruta
) {
    if (nodo == NULL) {
        return 0;
    }

    int errores = 0;

    switch (nodo->tipo) {

    case AST_PROGRAMA:
        for (size_t i = 0; i < nodo->cantidad_hijos; i++) {
            errores += revisar_nodo(
                nodo->hijos[i],
                ambito,
                ruta
            );
        }
        break;

    case AST_BLOQUE:
        errores += revisar_bloque(
            nodo,
            ambito,
            ruta
        );
        break;

    case AST_DECLARAR: {
        /* Revisar primero el inicializador. */
        errores += revisar_expresion(
            nodo->izquierda,
            ambito,
            ruta
        );

        /* No permitir redeclaraciones en el mismo ambito. */
        if (buscar_local(ambito, nodo->valor) != NULL) {
            fprintf(
                stdout,
                "%s:%d:%d: error E02: variable '%s' redeclarada\n",
                ruta,
                nodo->linea,
                nodo->columna,
                nodo->valor
            );

            errores++;
        }
        else {
            if (!declarar_variable(
                ambito,
                nodo->valor,
                nodo->izquierda != NULL
            )) {
                fprintf(
                    stderr,
                    "Error: limite de variables alcanzado.\n"
                );

                errores++;
            }
        }
        break;
    }

    case AST_ASIGNAR: {
        Simbolo* simbolo = buscar_variable(
            ambito,
            nodo->valor
        );

        if (simbolo == NULL) {
            fprintf(
                stdout,
                "%s:%d:%d: error E01: variable '%s' no declarada\n",
                ruta,
                nodo->linea,
                nodo->columna,
                nodo->valor
            );

            errores++;
        }

        int errores_expresion = revisar_expresion(
            nodo->izquierda,
            ambito,
            ruta
        );

        errores += errores_expresion;

        if (simbolo != NULL && errores_expresion == 0) {
            simbolo->inicializada = 1;
        }
        break;
    }

    case AST_IMPRIMIR:
        errores += revisar_expresion(
            nodo->izquierda,
            ambito,
            ruta
        );
        break;

    case AST_SI: {
        errores += revisar_expresion(
            nodo->izquierda,
            ambito,
            ruta
        );

        EstadoAmbito* original = guardar_estado(ambito);

        if (original == NULL) {
            fprintf(stderr, "Error: no se pudo guardar el estado.\n");
            return errores + 1;
        }

        /* Analizar la rama verdadera. */
        if (nodo->derecha != NULL) {
            errores += revisar_nodo(
                nodo->derecha,
                ambito,
                ruta
            );
        }

        EstadoAmbito* rama_si = guardar_estado(ambito);

        if (rama_si == NULL) {
            restaurar_estado(original);
            liberar_estado(original);
            fprintf(stderr, "Error: no se pudo guardar la rama if.\n");
            return errores + 1;
        }

        /* Recuperar el estado anterior para analizar else. */
        restaurar_estado(original);

        if (nodo->tercero != NULL) {
            errores += revisar_nodo(
                nodo->tercero,
                ambito,
                ruta
            );

            EstadoAmbito* rama_no = guardar_estado(ambito);

            if (rama_no == NULL) {
                restaurar_estado(original);
                liberar_estado(rama_si);
                liberar_estado(original);
                fprintf(stderr, "Error: no se pudo guardar la rama else.\n");
                return errores + 1;
            }

            /* Solo conservar variables inicializadas en ambas ramas. */
            combinar_estados(
                ambito,
                rama_si,
                rama_no
            );

            liberar_estado(rama_no);
        }
        else {
            /* Sin else, no podemos garantizar que se ejecute el if. */
            restaurar_estado(original);
        }

        liberar_estado(rama_si);
        liberar_estado(original);
        break;
    }

    case AST_MIENTRAS: {
        errores += revisar_expresion(
            nodo->izquierda,
            ambito,
            ruta
        );

        EstadoAmbito* original = guardar_estado(ambito);

        if (original == NULL) {
            fprintf(stderr, "Error: no se pudo guardar el estado.\n");
            return errores + 1;
        }

        if (nodo->derecha != NULL) {
            errores += revisar_nodo(
                nodo->derecha,
                ambito,
                ruta
            );
        }

        /* El ciclo podría ejecutarse cero veces. */
        restaurar_estado(original);
        liberar_estado(original);
        break;
    }

    case AST_BINARIA:
    case AST_NEG:
    case AST_VAR:
    case AST_NUM:
        errores += revisar_expresion(
            nodo,
            ambito,
            ruta
        );
        break;

    default:
        break;
    }

    return errores;
}

/* Punto de entrada del analisis semantico. */
int semantica_analizar(
    const AST* programa,
    const char* ruta
) {
    Ambito* global = crear_ambito(NULL);

    if (global == NULL) {
        fprintf(stderr, "Error: no se pudo crear el ambito global.\n");
        return 1;
    }

    int errores = revisar_nodo(
        programa,
        global,
        ruta
    );

    free(global);

    return errores;
}

