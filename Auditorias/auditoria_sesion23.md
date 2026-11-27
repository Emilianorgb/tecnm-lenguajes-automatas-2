# Bitácora de Requerimientos y Auditoría IA — Sesión 23
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Etiquetas y Saltos Incondicionales  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Generador de etiquetas e instrucciones goto  
Al desarrollar el código manualmente, la principal dificultad fue controlar el contador para generar etiquetas diferentes, sin repetir nombres. También tuve que cuidar el tamaño de los buffers y validar los apuntadores para evitar errores al construir las instrucciones.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Trazabilidad del flujo de control |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar dos funciones en lenguaje C para generar
etiquetas e instrucciones de salto incondicional.

La primera función se llamará nueva_etiqueta y deberá generar
nombres consecutivos como L0, L1, L2, utilizando un contador.

La segunda función se llamará emitir_flujo y deberá generar
instrucciones de flujo de control.

Requisitos:
1. Si es_salto es verdadero, generar GOTO seguido de la etiqueta.
2. Si es_salto es falso, generar la etiqueta seguida de dos puntos.
3. Validar los apuntadores y la capacidad del buffer.
4. Si la etiqueta es NULL, devolver una cadena vacía.
5. Utilizar snprintf para controlar el tamaño de las cadenas.
6. Respetar las firmas definidas en api_sesion23.h.
7. No incluir la función main.

Utiliza C99 y entrega código modular con análisis de complejidad.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion23.h"
#include <stdio.h>

void nueva_etiqueta(char *dst, int cap, int *contador) {
    if (dst == NULL || cap <= 0) {
        return;
    }

    dst[0] = '\0';

    if (contador == NULL) {
        return;
    }

    int longitud = snprintf(
        dst,
        (size_t)cap,
        "L%d",
        *contador
    );

    if (longitud >= 0) {
        (*contador)++;
    }
}

void emitir_flujo(char *dst, int cap,
                  const char *etiqueta, int es_salto) {
    if (dst == NULL || cap <= 0) {
        return;
    }

    dst[0] = '\0';

    if (etiqueta == NULL) {
        return;
    }

    const char *formato = es_salto ? "GOTO %s" : "%s:";

    snprintf(dst, (size_t)cap, formato, etiqueta);
}
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Saltos adelante y atrás estructurados

### Salida del harness
```text
=== AUDITORIA SESION 23 - Etiquetas y saltos incondicionales ===
Caso                               esperado:              obtenido:              resultado
[ 1] nueva_etiqueta(L0)                 esperado: L0           obtenido: L0           OK
[ 2] nueva_etiqueta(L5)                 esperado: L5           obtenido: L5           OK
[ 3] emitir_flujo(GOTO L2)              esperado: GOTO L2      obtenido: GOTO L2      OK
[ 4] emitir_flujo(marca L2)             esperado: L2:          obtenido: L2:          OK
[ 5] emitir_flujo(NULL)                 esperado:              obtenido:              OK
[ 6] nueva_etiqueta(L10)                esperado: L10          obtenido: L10          OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Un caso que debía considerarse era cuando la etiqueta recibida es NULL. Si no se valida, se puede intentar construir una instrucción con un apuntador inválido.

Para solucionarlo se agregó una condición que comprueba si la etiqueta existe antes de generar el texto. También se utiliza snprintf para limitar la escritura al espacio disponible y evitar desbordamientos del buffer.
> 

---
**Firma digital:** Emiliano Xooc Hau
