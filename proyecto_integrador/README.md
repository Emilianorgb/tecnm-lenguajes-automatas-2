# Lenguajito – Proyecto Integrador

Compilador desarrollado en lenguaje C para la asignatura **Lenguajes y Autómatas II**.

El proyecto consiste en desarrollar un compilador llamado Lenguajito, implementando progresivamente el análisis léxico, análisis sintáctico, análisis semántico y las etapas posteriores de generación de código.

## Integrantes del equipo

- Emiliano Xooc Hau
- Luis Enrique Noh Poot
- Jose Alfredo Nahuat Canul

## Repositorio

[GitHub – tecnm-lenguajes-automatas-2](https://github.com/Emilianorgb/tecnm-lenguajes-automatas-2)

## Tecnologías utilizadas

- Lenguaje C (C11).
- GCC.
- Makefile.
- Python 3 para ejecutar las pruebas.
- Ubuntu mediante WSL.

## Requisitos

Para compilar el proyecto se necesita:

- GCC.
- Make.
- Python 3.

## Estructura del proyecto

```text
proyecto_integrador/
├── src/
│   ├── ast.c
│   ├── compilador.c
│   ├── compilador.h
│   ├── lexer.c
│   ├── main.c
│   ├── parser.c
│   └── semantica.c
├── tests/
├── docs/
│   ├── avances.md
│   ├── entrega_hito1.md
│   ├── gramatica.md
│   └── guia-proyecto.md
├── Makefile
├── README.md
└── lenguajito
```

## Compilación

Desde la carpeta `proyecto_integrador`, ejecutar:

```bash
make clean
make
```

Para ejecutar las pruebas del Hito 1:

```bash
make test-hito1
```

## Modos de funcionamiento

### 1. Mostrar tokens

```bash
./lenguajito tests/hito1/01_expresion.lj --tokens
```

Muestra los elementos reconocidos por el analizador léxico, incluyendo palabras reservadas, identificadores, números y operadores.

### 2. Mostrar el AST

```bash
./lenguajito tests/hito1/01_expresion.lj --ast
```

Construye y muestra el árbol de sintaxis abstracta del programa.

### 3. Comprobar el programa

```bash
./lenguajito tests/hito1/01_expresion.lj --check
```

Realiza la comprobación sintáctica y el análisis semántico básico para detectar variables no declaradas.

## Estado actual del proyecto

### Funcionalidades implementadas

- Analizador léxico para reconocer palabras reservadas, identificadores, números, operadores y delimitadores.
- Reconocimiento y visualización de tokens mediante `--tokens`.
- Analizador sintáctico descendente recursivo.
- Construcción y visualización del árbol de sintaxis abstracta mediante `--ast`.
- Análisis semántico básico mediante `--check`.
- Detección de variables no declaradas mediante el diagnóstico `E01`.
- Compilación con GCC sin errores ni advertencias.
- Pruebas automatizadas del Hito 1: **4/4 superadas**.

### Funcionalidades pendientes

- Detección de variables redeclaradas mediante `E02`.
- Manejo completo de ámbitos y tabla de símbolos.
- Generación de código intermedio TAC.
- Optimización de código.
- Generación de ensamblador x86-64.
- Ejecución del programa compilado mediante `--run`.

Estas funcionalidades corresponden a los siguientes hitos del proyecto.

## Documentación

- [Guía del proyecto](docs/guia-proyecto.md)
- [Gramática de Lenguajito](docs/gramatica.md)
- [Bitácora de avances](docs/avances.md)
- [Auditoría de uso de IA – Hito 1](docs/entrega_hito1.md)

## Entrega del Hito 1

**Etiqueta:** `v0.1-hito1`

**Resultado de las pruebas:**

```text
Hito 1: 4/4 pruebas superadas
```

El Hito 1 contempla el análisis léxico, análisis sintáctico, construcción del AST y comprobación básica del programa.