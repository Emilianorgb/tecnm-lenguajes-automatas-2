# Proyecto Integrador · Lenguajito

Empieza por la **[guía del proyecto](docs/guia-proyecto.md)**: explica cómo se
trabaja, qué se entrega en cada hito y cómo se evalúa.

- Reglas y rúbrica: [`../PROYECTO.md`](../PROYECTO.md)
- Lenguaje, AST, diagnósticos y TAC: [`docs/gramatica.md`](docs/gramatica.md)
- Avances: [`docs/avances.md`](docs/avances.md)
- Pruebas: [`tests/`](tests/)

```bash
make            # construye ./lenguajito
make test       # ejecuta las pruebas del curso
make test-hito1 # solo las del Hito 1
```
## Estado del proyecto

### Qué funciona
- Analizador léxico para reconocer palabras reservadas, identificadores, números, operadores y delimitadores.
- Opción `--tokens` para mostrar los tokens reconocidos.
- Analizador sintáctico para construir el árbol de sintaxis abstracta (AST).
- Opción `--ast` para imprimir la estructura del AST.
- Opción `--check` para comprobar la sintaxis y detectar variables no declaradas mediante el diagnóstico `E01`.
- Pruebas del Hito 1: `make test-hito1` (4/4 superadas).

### Qué no funciona todavía
- Generación de código intermedio TAC.
- Generación de código ensamblador x86-64.
- Ejecución del programa compilado mediante `--run`.
- Manejo completo de ámbitos y análisis semántico avanzado.