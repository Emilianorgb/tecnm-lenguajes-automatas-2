
/* compilador.h - interfaz del compilador de Lenguajito. */

#ifndef COMPILADOR_H
#define COMPILADOR_H

#include <stddef.h>

/* Modos de ejecución del compilador:
 * --tokens, --ast, --check, --tac, --asm y --run.
 */
int compilar(const char* ruta, const char* modo);

/* Tipos de tokens del lenguaje. */
typedef enum {
    TOKEN_KW,
    TOKEN_ID,
    TOKEN_NUM,
    TOKEN_OP,
    TOKEN_DELIM,
    TOKEN_EOF
} TokenTipo;

/* Información de cada token. */
typedef struct {
    TokenTipo tipo;
    char* lexema;
    int linea;
    int columna;
} Token;

/* Analizador léxico. */
int lexer_analizar(
    const char* fuente,
    const char* ruta,
    Token** tokens,
    size_t* cantidad
);

/* Liberar memoria de los tokens. */
void lexer_liberar(Token* tokens, size_t cantidad);


/* Tipos de nodos del AST. */
typedef enum {
    AST_PROGRAMA,
    AST_BLOQUE,
    AST_DECLARAR,
    AST_ASIGNAR,
    AST_SI,
    AST_MIENTRAS,
    AST_IMPRIMIR,
    AST_BINARIA,
    AST_NEG,
    AST_NUM,
    AST_VAR
} ASTTipo;

/* Estructura de un nodo del AST. */
typedef struct AST {
    ASTTipo tipo;
    char* valor;
    struct AST* izquierda;
    struct AST* derecha;
    struct AST* tercero;
    struct AST** hijos;
    int linea;
    int columna;
    size_t cantidad_hijos;
} AST;

/* Funciones para manejar el AST. */
AST* ast_crear(ASTTipo tipo, const char* valor);
int ast_agregar_hijo(AST* padre, AST* hijo);
void ast_imprimir(const AST* nodo);
void ast_liberar(AST* nodo);

/* Analizador sintáctico. */
AST* parser_analizar(
    Token* tokens,
    size_t cantidad,
    const char* ruta
);

/* Analizador semantico. */
int semantica_analizar(
    const AST* programa,
    const char* ruta
);

#endif /* COMPILADOR_H */

