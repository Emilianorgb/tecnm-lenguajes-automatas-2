# Bitácora de Requerimientos y Auditoría IA — Sesión 21
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Fundamentos de Código de 3 Direcciones  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Representación en Cuádruplos (op,a,b,r)  
Al realizar el código manualmente, una de las dificultades fue llevar correctamente el contador de temporales para evitar que se repitieran los nombres. También fue necesario cuidar el espacio disponible en los arreglos de caracteres para no escribir fuera de sus límites.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Generación de temporales únicos (_t0..) |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar en lenguaje C dos funciones para generar código
intermedio de tres direcciones.

La primera función debe generar nombres temporales únicos utilizando
un contador, con nombres como _t0, _t1, _t2 y así sucesivamente.

La segunda función debe representar instrucciones mediante cuádruplos
con el formato (operador, argumento1, argumento2, resultado).

Utiliza C99, funciones modulares y snprintf para controlar el tamaño
de los arreglos de caracteres.

Considera los siguientes casos:
- Evitar nombres temporales repetidos.
- Validar los apuntadores y la capacidad del buffer.
- Representar argumentos NULL con un guion bajo.
- No incluir la función main en la implementación.

Entrega el código completo y explica brevemente su complejidad.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion21.h"
#include <stdio.h>

void nuevo_temporal(char *dst, int cap, int *contador) {
    if (dst == NULL || cap <= 0) {
        return;
    }

    dst[0] = '\0';

    if (contador == NULL) {
        return;
    }

    int numero = *contador;

    int longitud = snprintf(dst, (size_t)cap, "_t%d", numero);

    if (longitud >= 0) {
        (*contador)++;
    }
}

void emitir_cuadruplo(char *dst, int cap,
                      const char *op,
                      const char *a1,
                      const char *a2,
                      const char *res) {
    if (dst == NULL || cap <= 0) {
        return;
    }

    const char *operador = op != NULL ? op : "_";
    const char *arg1 = a1 != NULL ? a1 : "_";
    const char *arg2 = a2 != NULL ? a2 : "_";
    const char *resultado = res != NULL ? res : "_";

    snprintf(dst, (size_t)cap, "(%s, %s, %s, %s)",
             operador, arg1, arg2, resultado);
}
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Expresiones aritméticas compuestas

### Salida del harness
```text
=== AUDITORIA SESION 21 - Cuadruplos y temporales unicos ===
Caso                               esperado:              obtenido:              resultado
[ 1] nuevo_temporal(_t0)                esperado: _t0          obtenido: _t0          OK
[ 2] nuevo_temporal(_t7)                esperado: _t7          obtenido: _t7          OK
[ 3] cuadruplo de a + b
     esperado: (+, a, b, _t0)
     obtenido: (+, a, b, _t0)
     -> OK
[ 4] cuadruplo de _t0 * c
     esperado: (*, _t0, c, _t1)
     obtenido: (*, _t0, c, _t1)
     -> OK
[ 5] asignacion simple                  esperado: (=, a, _, x) obtenido: (=, a, _, x) OK
[ 6] goto sin operandos
     esperado: (goto, L1, _, _)
     obtenido: (goto, L1, _, _)
     -> OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
La IA debía considerar los argumentos nulos y el tamaño del buffer. Para evitar errores, se agregaron validaciones de apuntadores y capacidad, además de utilizar snprintf, que permite limitar la cantidad de caracteres escritos.

También se debe comprobar que el contador avance correctamente y que los nombres temporales no se repitan durante la generación de instrucciones.
> 

---
**Firma digital:** Emiliano Xooc Hau
