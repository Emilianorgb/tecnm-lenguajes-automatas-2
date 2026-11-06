
/* ast.c - Manejo del arbol de sintaxis abstracta de Lenguajito. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compilador.h"

/* Crear una copia de una cadena. */
static char* ast_copiar_texto(const char* texto) {
    if (texto == NULL) {
        return NULL;
    }

    size_t longitud = strlen(texto);

    char* copia = malloc(longitud + 1);

    if (copia == NULL) {
        return NULL;
    }

    memcpy(copia, texto, longitud + 1);

    return copia;
}

/* Crear un nodo del AST. */
AST* ast_crear(ASTTipo tipo, const char* valor) {
    AST* nodo = calloc(1, sizeof(AST));

    if (nodo == NULL) {
        return NULL;
    }

    nodo->tipo = tipo;
    nodo->valor = ast_copiar_texto(valor);

    if (valor != NULL && nodo->valor == NULL) {
        free(nodo);
        return NULL;
    }

    return nodo;
}

/* Agregar un hijo a un nodo. */
int ast_agregar_hijo(AST* padre, AST* hijo) {
    if (padre == NULL || hijo == NULL) {
        return 0;
    }

    AST** nuevos = realloc(
        padre->hijos,
        (padre->cantidad_hijos + 1) * sizeof(AST*)
    );

    if (nuevos == NULL) {
        return 0;
    }

    padre->hijos = nuevos;
    padre->hijos[padre->cantidad_hijos] = hijo;
    padre->cantidad_hijos++;

    return 1;
}

/* Imprimir un nodo del AST. */
void ast_imprimir(const AST* nodo) {
    if (nodo == NULL) {
        return;
    }

    switch (nodo->tipo) {

    case AST_PROGRAMA:
        printf("(programa");
        break;

    case AST_BLOQUE:
        printf("(bloque");
        break;

    case AST_DECLARAR:
        printf("(declarar %s", nodo->valor);
        if (nodo->izquierda != NULL) {
            printf(" ");
            ast_imprimir(nodo->izquierda);
        }
        printf(")");
        return;

    case AST_ASIGNAR:
        printf("(asignar %s ", nodo->valor);
        ast_imprimir(nodo->izquierda);
        printf(")");
        return;

    case AST_SI:
        printf("(si ");
        ast_imprimir(nodo->izquierda);

        printf(" (entonces ");
        ast_imprimir(nodo->derecha);
        printf(")");

        if (nodo->tercero != NULL) {
            printf(" (si_no ");
            ast_imprimir(nodo->tercero);
            printf(")");
        }

        printf(")");
        return;

    case AST_MIENTRAS:
        printf("(mientras ");
        ast_imprimir(nodo->izquierda);
        printf(" ");
        ast_imprimir(nodo->derecha);
        printf(")");
        return;

    case AST_IMPRIMIR:
        printf("(imprimir ");
        ast_imprimir(nodo->izquierda);
        printf(")");
        return;

    case AST_BINARIA:
        printf("(%s ", nodo->valor);
        ast_imprimir(nodo->izquierda);
        printf(" ");
        ast_imprimir(nodo->derecha);
        printf(")");
        return;

    case AST_NEG:
        printf("(neg ");
        ast_imprimir(nodo->izquierda);
        printf(")");
        return;

    case AST_NUM:
        printf("(num %s)", nodo->valor);
        return;

    case AST_VAR:
        printf("(var %s)", nodo->valor);
        return;
    }

    for (size_t i = 0; i < nodo->cantidad_hijos; i++) {
        printf(" ");
        ast_imprimir(nodo->hijos[i]);
    }

    printf(")");
}

/* Liberar toda la memoria del AST. */
void ast_liberar(AST* nodo) {
    if (nodo == NULL) {
        return;
    }

    ast_liberar(nodo->izquierda);
    ast_liberar(nodo->derecha);
    ast_liberar(nodo->tercero);

    for (size_t i = 0; i < nodo->cantidad_hijos; i++) {
        ast_liberar(nodo->hijos[i]);
    }

    free(nodo->hijos);
    free(nodo->valor);
    free(nodo);
}
