# Auditoría de uso de Inteligencia Artificial – Hito 1

## 1. Información del proyecto

- **Proyecto:** Lenguajito – Compilador
- **Asignatura:** Lenguajes y Autómatas II
- **Equipo:** Emiliano Xooc Hau, Luis Enrique Noh Poot y Jose Alfredo Nahuat Canul.
- **Repositorio:** https://github.com/Emilianorgb/tecnm-lenguajes-automatas-2
- **Hito:** 1 – Léxico, sintaxis y AST
- **Etiqueta:** `v0.1-hito1`

## 2. Herramienta de inteligencia artificial utilizada

Se utilizó ChatGPT como herramienta de apoyo durante el desarrollo del proyecto.

La IA ayudó a explicar conceptos de programación en C, analizar errores, proponer fragmentos de código, revisar resultados de pruebas y orientar sobre la documentación y el uso de Git.

## 3. Bitácora C-R-E-O

| C – Consulta | R – Respuesta de IA | E – Evaluación del equipo | O – Observación y resultado |
|---|---|---|---|
| ¿Cómo implementar el analizador léxico? | Explicaciones y sugerencias para reconocer palabras reservadas, identificadores, números y operadores. | Se revisaron las sugerencias y se comprobaron con la compilación y las pruebas. | Se consiguió reconocer los tokens del lenguaje. |
| ¿Cómo construir el árbol de sintaxis abstracta? | Orientación sobre el parser descendente recursivo y la construcción de nodos AST. | Se revisó la estructura generada y se ejecutó el modo `--ast`. | El compilador muestra la estructura del programa. |
| ¿Cómo detectar variables no declaradas? | Se proporcionaron explicaciones y sugerencias para el análisis semántico básico y el diagnóstico E01. | Se revisó el código y se ejecutaron programas de prueba. | Se implementó la detección básica de variables no declaradas. |
| ¿Cómo corregir errores de compilación? | Se analizaron mensajes de error y se propusieron posibles correcciones. | Se aplicaron las correcciones necesarias y se volvió a compilar. | La compilación terminó sin errores ni advertencias. |
| ¿Cómo comprobar el funcionamiento del proyecto? | Se explicó cómo utilizar Makefile y ejecutar las pruebas automatizadas. | Se ejecutaron los comandos en Ubuntu mediante WSL. | Se aprobaron las 4 pruebas del Hito 1. |
| ¿Cómo organizar la documentación y GitHub? | Se proporcionó orientación para elaborar el README, la bitácora y administrar commits, ramas y etiquetas. | Se revisaron los archivos y se verificó la sincronización con GitHub. | Se actualizaron los documentos y se publicó el avance del proyecto. |

## 4. Participación de la IA

La inteligencia artificial fue utilizada como apoyo durante el desarrollo, proporcionando explicaciones, ejemplos, sugerencias de código y orientación para resolver problemas.

Las respuestas fueron revisadas por el equipo. Los integrantes realizaron las modificaciones, ejecutaron los comandos, comprobaron la compilación y verificaron los resultados obtenidos.

## 5. Verificación del proyecto

Se realizaron las siguientes comprobaciones:

```bash
make clean
make
make test-hito1
```

Resultado:

```text
Hito 1: 4/4 pruebas superadas
```

También se comprobaron los siguientes modos:

- `--tokens`: muestra los tokens reconocidos.
- `--ast`: imprime el árbol de sintaxis abstracta.
- `--check`: realiza la comprobación sintáctica y semántica básica.

## 6. Conclusión

El uso de inteligencia artificial permitió contar con apoyo para comprender conceptos, resolver problemas de programación y organizar el desarrollo del compilador.

El equipo revisó las sugerencias y comprobó el funcionamiento del código mediante compilaciones y pruebas. La responsabilidad del desarrollo y de los resultados obtenidos corresponde a los integrantes del equipo.

La IA fue una herramienta de apoyo y no sustituyó el aprendizaje ni la participación de los integrantes.