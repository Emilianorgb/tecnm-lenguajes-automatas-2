
/* compilador.c - punto de entrada del compilador de Lenguajito. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compilador.h"

/* Obtener el nombre del tipo de token. */
static const char* nombre_tipo(TokenTipo tipo) {
    switch (tipo) {
    case TOKEN_KW:    return "KW";
    case TOKEN_ID:    return "ID";
    case TOKEN_NUM:   return "NUM";
    case TOKEN_OP:    return "OP";
    case TOKEN_DELIM: return "DELIM";
    case TOKEN_EOF:   return "EOF";
    }

    return "DESCONOCIDO";
}

/* Leer el contenido completo de un archivo. */
static char* leer_archivo(const char* ruta) {
    FILE* archivo = fopen(ruta, "rb");

    if (archivo == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo: %s\n", ruta);
        return NULL;
    }

    if (fseek(archivo, 0, SEEK_END) != 0) {
        fclose(archivo);
        return NULL;
    }

    long tamano = ftell(archivo);

    if (tamano < 0 || fseek(archivo, 0, SEEK_SET) != 0) {
        fclose(archivo);
        return NULL;
    }

    char* contenido = malloc((size_t)tamano + 1);

    if (contenido == NULL) {
        fclose(archivo);
        return NULL;
    }

    size_t leidos = fread(contenido, 1, (size_t)tamano, archivo);

    if (leidos != (size_t)tamano || ferror(archivo)) {
        free(contenido);
        fclose(archivo);
        return NULL;
    }

    contenido[leidos] = '\0';
    fclose(archivo);

    return contenido;
}

/* Imprimir todos los tokens. */
static void imprimir_tokens(Token* tokens, size_t cantidad) {
    for (size_t i = 0; i < cantidad; i++) {
        printf(
            "%d:%d %s %s\n",
            tokens[i].linea,
            tokens[i].columna,
            nombre_tipo(tokens[i].tipo),
            tokens[i].lexema
        );
    }
}

/* Ejecutar el compilador. */
int compilar(const char* ruta, const char* modo) {
    char* fuente = leer_archivo(ruta);

    if (fuente == NULL) {
        return 1;
    }

    Token* tokens = NULL;
    size_t cantidad = 0;

    int resultado = lexer_analizar(
        fuente,
        ruta,
        &tokens,
        &cantidad
    );

    free(fuente);

    if (resultado != 0) {
        lexer_liberar(tokens, cantidad);
        return 1;
    }

    /* Modo de impresion de tokens. */
    if (strcmp(modo, "--tokens") == 0) {
        imprimir_tokens(tokens, cantidad);
        lexer_liberar(tokens, cantidad);
        return 0;
    }

    /* Construir el AST. */
    AST* programa = parser_analizar(
        tokens,
        cantidad,
        ruta
    );

    lexer_liberar(tokens, cantidad);

    if (programa == NULL) {
        return 1;
    }

    /* Modo de impresion del AST. */
    if (strcmp(modo, "--ast") == 0) {
        ast_imprimir(programa);
        printf("\n");
    }

    /* --check solamente comprueba el programa. */
    else if (strcmp(modo, "--check") == 0) {
        /* No necesita imprimir nada. */
    }

    else {
        fprintf(
            stderr,
            "El modo %s todavia no esta implementado.\n",
            modo
        );

        ast_liberar(programa);
        return 2;
    }

    ast_liberar(programa);

    return 0;
}
