
/* interprete.c - Ejecutor del lenguaje Lenguajito. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "compilador.h"

#define MAX_VARIABLES 256
#define MAX_NOMBRE 128

/* Variable almacenada durante la ejecucion. */
typedef struct {
    char nombre[MAX_NOMBRE];
    long long valor;
} Variable;

/* Ambitos anidados. */
typedef struct Ambito {
    Variable variables[MAX_VARIABLES];
    int cantidad;
    struct Ambito* padre;
} Ambito;

/* Crear un nuevo ambito. */
static Ambito* crear_ambito(Ambito* padre) {
    Ambito* nuevo = calloc(1, sizeof(Ambito));

    if (nuevo != NULL) {
        nuevo->padre = padre;
    }

    return nuevo;
}

/* Buscar una variable en el ambito actual y sus padres. */
static Variable* buscar_variable(
    Ambito* ambito,
    const char* nombre
) {
    while (ambito != NULL) {
        for (int i = 0; i < ambito->cantidad; i++) {
            if (strcmp(ambito->variables[i].nombre, nombre) == 0) {
                return &ambito->variables[i];
            }
        }

        ambito = ambito->padre;
    }

    return NULL;
}

/* Buscar una variable solamente en el ambito actual. */
static Variable* buscar_local(
    Ambito* ambito,
    const char* nombre
) {
    for (int i = 0; i < ambito->cantidad; i++) {
        if (strcmp(ambito->variables[i].nombre, nombre) == 0) {
            return &ambito->variables[i];
        }
    }

    return NULL;
}

/* Crear una variable en el ambito actual. */
static int declarar_variable(
    Ambito* ambito,
    const char* nombre,
    long long valor
) {
    if (ambito->cantidad >= MAX_VARIABLES ||
        strlen(nombre) >= MAX_NOMBRE ||
        buscar_local(ambito, nombre) != NULL) {
        return 0;
    }

    Variable* variable = &ambito->variables[ambito->cantidad++];

    snprintf(
        variable->nombre,
        sizeof(variable->nombre),
        "%s",
        nombre
    );

    variable->valor = valor;

    return 1;
}

/* Declaraciones anticipadas. */
static int evaluar_expresion(
    const AST* nodo,
    Ambito* ambito,
    const char* ruta,
    long long* resultado
);

static int ejecutar_nodo(
    const AST* nodo,
    Ambito* ambito,
    const char* ruta
);

/* Evaluar una expresion. */
static int evaluar_expresion(
    const AST* nodo,
    Ambito* ambito,
    const char* ruta,
    long long* resultado
) {
    if (nodo == NULL || resultado == NULL) {
        return 1;
    }

    long long izquierda = 0;
    long long derecha = 0;
    char* fin = NULL;

    switch (nodo->tipo) {

    case AST_NUM:
    errno = 0;
    *resultado = strtoll(nodo->valor, &fin, 10);

    if (fin == nodo->valor || *fin != '\0') {
        fprintf(stderr, "Numero invalido en %s\n", ruta);
        return 1;
    }

    if (errno == ERANGE) {
        fprintf(
            stderr,
            "%s:%d:%d: error E05: numero fuera del rango permitido\n",
            ruta,
            nodo->linea,
            nodo->columna
        );
        return 1;
    }

    return 0;

    case AST_VAR: {
        Variable* variable = buscar_variable(
            ambito,
            nodo->valor
        );

        if (variable == NULL) {
            fprintf(
                stderr,
                "%s:%d:%d: error E01: variable '%s' no declarada\n",
                ruta,
                nodo->linea,
                nodo->columna,
                nodo->valor
            );

            return 1;
        }

        *resultado = variable->valor;
        return 0;
    }

    case AST_NEG:
    if (evaluar_expresion(
        nodo->izquierda,
        ambito,
        ruta,
        &izquierda
    ) != 0) {
        return 1;
    }

    if (izquierda == LLONG_MIN) {
        fprintf(
            stderr,
            "%s:%d:%d: error E05: desbordamiento numerico en negacion\n",
            ruta,
            nodo->linea,
            nodo->columna
        );

        return 1;
    }

    *resultado = -izquierda;
    return 0;

    case AST_BINARIA:
        if (evaluar_expresion(
            nodo->izquierda,
            ambito,
            ruta,
            &izquierda
        ) != 0 ||
            evaluar_expresion(
                nodo->derecha,
                ambito,
                ruta,
                &derecha
            ) != 0) {
            return 1;
        }

        if (strcmp(nodo->valor, "+") == 0) {
            if (__builtin_add_overflow(izquierda, derecha, resultado)) {
                goto desbordamiento;
            }
        }
        else if (strcmp(nodo->valor, "-") == 0) {
            if (__builtin_sub_overflow(izquierda, derecha, resultado)) {
                goto desbordamiento;
            }
        }
        else if (strcmp(nodo->valor, "*") == 0) {
            if (__builtin_mul_overflow(izquierda, derecha, resultado)) {
                goto desbordamiento;
            }
        }
        else if (strcmp(nodo->valor, "/") == 0) {
            if (derecha == 0) {
                fprintf(
                    stderr,
                    "%s:%d:%d: error E04: division entre cero\n",
                    ruta,
                    nodo->linea,
                    nodo->columna
                );

                return 1;
            }

            if (izquierda == LLONG_MIN && derecha == -1) {
                goto desbordamiento;
            }

            *resultado = izquierda / derecha;
        }
        else if (strcmp(nodo->valor, "<") == 0) {
            *resultado = izquierda < derecha;
        }
        else if (strcmp(nodo->valor, ">") == 0) {
            *resultado = izquierda > derecha;
        }
        else if (strcmp(nodo->valor, "<=") == 0) {
            *resultado = izquierda <= derecha;
        }
        else if (strcmp(nodo->valor, ">=") == 0) {
            *resultado = izquierda >= derecha;
        }
        else if (strcmp(nodo->valor, "==") == 0) {
            *resultado = izquierda == derecha;
        }
        else if (strcmp(nodo->valor, "!=") == 0) {
            *resultado = izquierda != derecha;
        }
        else {
            fprintf(stderr, "Operador desconocido: %s\n", nodo->valor);
            return 1;
        }

        return 0;

    desbordamiento:
        fprintf(
            stderr,
            "%s:%d:%d: error E05: desbordamiento numerico\n",
            ruta,
            nodo->linea,
            nodo->columna
        );

        return 1;

    default:
        fprintf(stderr, "Expresion no reconocida en %s\n", ruta);
        return 1;
    }
}

/* Ejecutar un bloque con un nuevo ambito. */
static int ejecutar_bloque(
    const AST* nodo,
    Ambito* padre,
    const char* ruta
) {
    Ambito* local = crear_ambito(padre);

    if (local == NULL) {
        fprintf(stderr, "No se pudo crear un ambito.\n");
        return 1;
    }

    int errores = 0;

    for (size_t i = 0; i < nodo->cantidad_hijos; i++) {
        if (ejecutar_nodo(
            nodo->hijos[i],
            local,
            ruta
        ) != 0) {
            errores = 1;
            break;
        }
    }

    free(local);
    return errores;
}

/* Ejecutar una instruccion. */
static int ejecutar_nodo(
    const AST* nodo,
    Ambito* ambito,
    const char* ruta
) {
    if (nodo == NULL) {
        return 0;
    }

    long long valor = 0;

    switch (nodo->tipo) {

    case AST_PROGRAMA:
        for (size_t i = 0; i < nodo->cantidad_hijos; i++) {
            if (ejecutar_nodo(
                nodo->hijos[i],
                ambito,
                ruta
            ) != 0) {
                return 1;
            }
        }
        return 0;

    case AST_BLOQUE:
        return ejecutar_bloque(nodo, ambito, ruta);

    case AST_DECLARAR:
        if (nodo->izquierda != NULL &&
            evaluar_expresion(
                nodo->izquierda,
                ambito,
                ruta,
                &valor
            ) != 0) {
            return 1;
        }

        if (!declarar_variable(ambito, nodo->valor, valor)) {
            fprintf(
                stderr,
                "%s:%d:%d: error E02: variable '%s' redeclarada\n",
                ruta,
                nodo->linea,
                nodo->columna,
                nodo->valor
            );

            return 1;
        }

        return 0;

    case AST_ASIGNAR: {
        Variable* variable = buscar_variable(
            ambito,
            nodo->valor
        );

        if (variable == NULL) {
            fprintf(
                stderr,
                "%s:%d:%d: error E01: variable '%s' no declarada\n",
                ruta,
                nodo->linea,
                nodo->columna,
                nodo->valor
            );

            return 1;
        }

        if (evaluar_expresion(
            nodo->izquierda,
            ambito,
            ruta,
            &valor
        ) != 0) {
            return 1;
        }

        variable->valor = valor;
        return 0;
    }

    case AST_IMPRIMIR:
        if (evaluar_expresion(
            nodo->izquierda,
            ambito,
            ruta,
            &valor
        ) != 0) {
            return 1;
        }

        printf("%lld\n", valor);
        return 0;

    case AST_SI:
        if (evaluar_expresion(
            nodo->izquierda,
            ambito,
            ruta,
            &valor
        ) != 0) {
            return 1;
        }

        if (valor != 0) {
            return ejecutar_nodo(
                nodo->derecha,
                ambito,
                ruta
            );
        }

        if (nodo->tercero != NULL) {
            return ejecutar_nodo(
                nodo->tercero,
                ambito,
                ruta
            );
        }

        return 0;

    case AST_MIENTRAS:
        while (1) {
            if (evaluar_expresion(
                nodo->izquierda,
                ambito,
                ruta,
                &valor
            ) != 0) {
                return 1;
            }

            if (valor == 0) {
                break;
            }

            if (ejecutar_nodo(
                nodo->derecha,
                ambito,
                ruta
            ) != 0) {
                return 1;
            }
        }

        return 0;

    default:
        fprintf(stderr, "Instruccion no reconocida en %s\n", ruta);
        return 1;
    }
}

/* Punto de entrada del interprete. */
int interprete_ejecutar(
    const AST* programa,
    const char* ruta
) {
    Ambito* global = crear_ambito(NULL);

    if (global == NULL) {
        fprintf(stderr, "No se pudo crear el ambito global.\n");
        return 1;
    }

    int resultado = ejecutar_nodo(
        programa,
        global,
        ruta
    );

    free(global);
    return resultado;
}
