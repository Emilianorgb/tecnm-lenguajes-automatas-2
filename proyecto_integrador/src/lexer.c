/* lexer.c - Analizador lexico de Lenguajito. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

/* Comprobar si un caracter es una letra. */
static int es_letra(char c) {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

/* Comprobar si un caracter es un digito. */
static int es_digito(char c) {
    return c >= '0' && c <= '9';
}

/* Comprobar si es espacio en blanco. */
static int es_espacio(char c) {
    return c == ' ' || c == '\t' ||
        c == '\n' || c == '\r';
}

/* Comprobar si una palabra es reservada. */
static int es_reservada(const char* palabra) {
    const char* reservadas[] = {
        "int", "if", "else", "while", "print"
    };

    size_t total = sizeof(reservadas) / sizeof(reservadas[0]);

    for (size_t i = 0; i < total; i++) {
        if (strcmp(palabra, reservadas[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

/* Crear una copia del lexema. */
static char* copiar_lexema(const char* inicio, size_t longitud) {
    char* copia = malloc(longitud + 1);

    if (copia == NULL) {
        return NULL;
    }

    memcpy(copia, inicio, longitud);
    copia[longitud] = '\0';

    return copia;
}

/* Agregar un token al arreglo. */
static int agregar_token(
    Token** tokens,
    size_t* cantidad,
    TokenTipo tipo,
    const char* inicio,
    size_t longitud,
    int linea,
    int columna
) {
    Token* nuevo = realloc(
        *tokens,
        (*cantidad + 1) * sizeof(Token)
    );

    if (nuevo == NULL) {
        return 0;
    }

    *tokens = nuevo;

    Token* token = &nuevo[*cantidad];

    token->tipo = tipo;
    token->lexema = copiar_lexema(inicio, longitud);
    token->linea = linea;
    token->columna = columna;

    if (token->lexema == NULL) {
        return 0;
    }

    (*cantidad)++;

    return 1;
}

/* Liberar la memoria de los tokens. */
void lexer_liberar(Token* tokens, size_t cantidad) {
    for (size_t i = 0; i < cantidad; i++) {
        free(tokens[i].lexema);
    }

    free(tokens);
}

/* Analizar el codigo fuente. */
int lexer_analizar(
    const char* fuente,
    const char* ruta,
    Token** tokens,
    size_t* cantidad
) {
    if (fuente == NULL || ruta == NULL ||
        tokens == NULL || cantidad == NULL) {
        return 1;
    }

    *tokens = NULL;
    *cantidad = 0;

    const char* actual = fuente;
    int linea = 1;
    int columna = 1;
    int errores = 0;

    while (*actual != '\0') {

        /* Ignorar espacios. */
        if (es_espacio(*actual)) {
            if (*actual == '\n' || *actual == '\r') {
                if (*actual == '\r' && actual[1] == '\n') {
                    actual++;
                }

                linea++;
                columna = 1;
            }
            else {
                columna++;
            }

            actual++;
            continue;
        }

        /* Ignorar comentarios de una linea. */
        if (actual[0] == '/' && actual[1] == '/') {
            while (*actual != '\0' &&
                *actual != '\n' &&
                *actual != '\r') {
                actual++;
                columna++;
            }

            continue;
        }

        const char* inicio = actual;
        int linea_inicio = linea;
        int columna_inicio = columna;
        TokenTipo tipo;
        size_t longitud = 1;

        /* Identificadores y palabras reservadas. */
        if (es_letra(*actual)) {
            actual++;
            columna++;

            while (es_letra(*actual) || es_digito(*actual)) {
                actual++;
                columna++;
            }

            longitud = (size_t)(actual - inicio);

            char* palabra = copiar_lexema(inicio, longitud);

            if (palabra == NULL) {
                errores++;
                break;
            }

            tipo = es_reservada(palabra) ? TOKEN_KW : TOKEN_ID;
            free(palabra);
        }

        /* Numeros enteros. */
        else if (es_digito(*actual)) {
            actual++;
            columna++;

            while (es_digito(*actual)) {
                actual++;
                columna++;
            }

            longitud = (size_t)(actual - inicio);
            tipo = TOKEN_NUM;
        }

        /* Operadores. */
        else if (
            *actual == '+' || *actual == '-' ||
            *actual == '*' || *actual == '/' ||
            *actual == '<' || *actual == '>' ||
            *actual == '=' || *actual == '!'
            ) {
            tipo = TOKEN_OP;

            if (
                (actual[0] == '<' || actual[0] == '>' ||
                    actual[0] == '=' || actual[0] == '!') &&
                actual[1] == '='
                ) {
                longitud = 2;
            }

            actual += longitud;
            columna += (int)longitud;
        }

        /* Delimitadores. */
        else if (
            *actual == '(' || *actual == ')' ||
            *actual == '{' || *actual == '}' ||
            *actual == ';'
            ) {
            tipo = TOKEN_DELIM;
            actual++;
            columna++;
        }

        /* Caracter invalido. */
        else {
            fprintf(
                stdout,
                "%s:%d:%d: error S01: caracter invalido '%c'\n",
                ruta,
                linea,
                columna,
                *actual
            );

            errores++;
            actual++;
            columna++;
            continue;
        }

        /* Guardar el token reconocido. */
        if (!agregar_token(
            tokens,
            cantidad,
            tipo,
            inicio,
            longitud,
            linea_inicio,
            columna_inicio
        )) {
            errores++;
            break;
        }
    }

    /* Agregar el token de fin de archivo. */
    if (!agregar_token(
        tokens,
        cantidad,
        TOKEN_EOF,
        "",
        0,
        linea,
        columna
    )) {
        errores++;
    }

    return errores > 0 ? 1 : 0;
}
