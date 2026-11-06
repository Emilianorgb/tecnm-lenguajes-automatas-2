
/* semantica.c - Analisis semantico de Lenguajito. */

#include <stdio.h>
#include <string.h>

#include "compilador.h"

#define MAX_VARIABLES 256

typedef struct {
    char nombres[MAX_VARIABLES][128];
    int cantidad;
} TablaSimbolos;

/* Buscar una variable en la tabla. */
static int buscar_variable(
    TablaSimbolos* tabla,
    const char* nombre
) {
    for (int i = 0; i < tabla->cantidad; i++) {
        if (strcmp(tabla->nombres[i], nombre) == 0) {
            return 1;
        }
    }

    return 0;
}

/* Registrar una variable declarada. */
static void declarar_variable(
    TablaSimbolos* tabla,
    const char* nombre
) {
    if (tabla->cantidad >= MAX_VARIABLES ||
        buscar_variable(tabla, nombre)) {
        return;
    }

    snprintf(
        tabla->nombres[tabla->cantidad],
        sizeof(tabla->nombres[tabla->cantidad]),
        "%s",
        nombre
    );

    tabla->cantidad++;
}

/* Revisar las variables utilizadas en una expresion. */
static int revisar_expresion(
    const AST* nodo,
    TablaSimbolos* tabla,
    const char* ruta
) {
    if (nodo == NULL) {
        return 0;
    }

    int errores = 0;

    if (nodo->tipo == AST_VAR &&
        !buscar_variable(tabla, nodo->valor)) {
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

    errores += revisar_expresion(
        nodo->izquierda, tabla, ruta
    );

    errores += revisar_expresion(
        nodo->derecha, tabla, ruta
    );

    return errores;
}

/* Revisar las instrucciones del programa. */
static int revisar_nodo(
    const AST* nodo,
    TablaSimbolos* tabla,
    const char* ruta
) {
    if (nodo == NULL) {
        return 0;
    }

    int errores = 0;

    switch (nodo->tipo) {

    case AST_DECLARAR:
        errores += revisar_expresion(
            nodo->izquierda, tabla, ruta
        );

        declarar_variable(tabla, nodo->valor);
        break;

    case AST_ASIGNAR:
        if (!buscar_variable(tabla, nodo->valor)) {
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

        errores += revisar_expresion(
            nodo->izquierda, tabla, ruta
        );
        break;

    case AST_IMPRIMIR:
        errores += revisar_expresion(
            nodo->izquierda, tabla, ruta
        );
        break;

    case AST_BINARIA:
    case AST_NEG:
        errores += revisar_expresion(nodo, tabla, ruta);
        break;

    case AST_SI:
    case AST_MIENTRAS:
        errores += revisar_expresion(
            nodo->izquierda, tabla, ruta
        );

        errores += revisar_nodo(
            nodo->derecha, tabla, ruta
        );

        errores += revisar_nodo(
            nodo->tercero, tabla, ruta
        );
        break;

    case AST_PROGRAMA:
    case AST_BLOQUE:
        for (size_t i = 0; i < nodo->cantidad_hijos; i++) {
            errores += revisar_nodo(
                nodo->hijos[i], tabla, ruta
            );
        }
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
    TablaSimbolos tabla = { .cantidad = 0 };

    return revisar_nodo(programa, &tabla, ruta);
}
