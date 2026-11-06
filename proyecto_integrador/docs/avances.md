# Avances del proyecto

**Equipo:** Emiliano Xooc Hau, Luis Enrique Noh Poot y Jose Alfredo Nahuat Canul.

**Repositorio:** https://github.com/Emilianorgb/tecnm-lenguajes-automatas-2

**Tag actual:** `v0.1-hito1`

---

## Avance 0 · Sesión 05 · Hito 0

1. **Qué compila hoy (comando exacto):** Se preparó la estructura inicial del proyecto y el entorno de trabajo.
2. **Qué falla y por qué:** Todavía no se tenía implementado el compilador ni el reconocimiento de instrucciones.
3. **Qué sigue:** Crear los archivos principales del proyecto y comenzar con el análisis léxico.
4. **Commit:** No se tiene registrado el hash de esta sesión.

---

## Avance 1 · Sesión 08

1. **Qué compila hoy (comando exacto):** Se comenzó a trabajar con el código en C y la estructura del compilador.
2. **Qué falla y por qué:** Faltaba completar el reconocimiento de tokens y el análisis de la sintaxis.
3. **Qué sigue:** Terminar el lexer y comenzar a implementar el parser.
4. **Commit:** No se tiene registrado el hash de esta sesión.

---

## Avance 2 · Sesión 15

1. **Qué compila hoy (comando exacto):** `make clean && make`
2. **Qué falla y por qué:** Faltaba completar el análisis semántico y revisar los errores de variables no declaradas.
3. **Qué sigue:** Implementar el análisis semántico básico y mejorar los mensajes de error.
4. **Commit:** `c5418fe` — Hito 1: implementar lexer y parser de Lenguajito.

---

## Avance 3 · Sesión 25

1. **Qué compila hoy (comando exacto):** Pendiente de implementación y comprobación para esta etapa.
2. **Qué falla y por qué:** Todavía no se ha completado la generación de código intermedio y las optimizaciones.
3. **Qué sigue:** Implementar el código de tres direcciones (TAC), el plegado de constantes y la eliminación de código muerto.
4. **Commit:** Pendiente.

---

## Avance 4 · Sesión 35

1. **Qué compila hoy (comando exacto):** Pendiente de implementación y comprobación para esta etapa.
2. **Qué falla y por qué:** Todavía falta completar la generación de código ensamblador y la ejecución del programa compilado.
3. **Qué sigue:** Implementar el ensamblador x86-64 y realizar las pruebas finales.
4. **Commit:** Pendiente.

---

## Avance actual · Hito 1

1. **Qué compila hoy (comando exacto):**
   - `make clean`
   - `make`
   - `make test-hito1`

   **Resultado:** La compilación terminó correctamente y se superaron las 4 de 4 pruebas.

2. **Qué falla y por qué:**
   - El análisis semántico está implementado de forma básica y todavía necesita ampliarse.
   - Falta completar la tabla de símbolos y los ámbitos.
   - Todavía no se genera código intermedio TAC.
   - Falta implementar la generación de código ensamblador x86-64.
   - La ejecución mediante `--run` está pendiente.

3. **Qué sigue:**
   - Completar el análisis semántico.
   - Detectar variables redeclaradas mediante el error E02.
   - Implementar los ámbitos y mejorar los diagnósticos.
   - Continuar con los requisitos del Hito 2.

4. **Commit:** `40f8fc0` — `feat: integrar analisis semantico basico`.

**Tag de entrega:** `v0.1-hito1`

---

## Resultado de las pruebas

Se ejecutaron los siguientes comandos:

```bash
make clean
make
make test-hito1
```

El resultado fue:

```text
Hito 1: 4/4 pruebas superadas
```

También se comprobaron los modos:

- `--tokens`: reconoce los tokens del lenguaje.
- `--ast`: muestra el árbol de sintaxis abstracta.
- `--check`: realiza la revisión semántica básica.

**Estado:** Hito 1 compilado y probado correctamente.