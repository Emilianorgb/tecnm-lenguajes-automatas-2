# Bitácora de Requerimientos y Auditoría IA — Sesión 25
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Control de Flujo: Bucles while y for  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Estructura de ciclo en instrucciones TAC  
Al realizar la implementación manual identifiqué que una de las dificultades fue controlar el orden de las instrucciones que forman un ciclo. También tuve que cuidar la capacidad del arreglo para no escribir fuera de sus límites. Otro punto importante fue manejar correctamente las etiquetas de inicio y final, evitando que se repitan cuando se generan varios ciclos.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Garantía de actualización de iterador |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar en lenguaje C99 dos funciones para generar
instrucciones TAC de ciclos while y for.

La función emitir_while debe generar una etiqueta de inicio,
una instrucción condicional IFFALSE, un salto GOTO al inicio
y una etiqueta de salida.

La función emitir_for debe considerar la inicialización,
la etiqueta de inicio, la condición, la actualización del
iterador, el salto de regreso y la etiqueta final.

Las dos funciones deben respetar las firmas establecidas
en el archivo api_sesion25.h.

Valida los apuntadores, la capacidad máxima del arreglo y
los argumentos recibidos. Evita escribir instrucciones
incompletas si no existe espacio suficiente.

Utiliza C99, funciones estándar y código modular.
Incluye un análisis de complejidad temporal y espacial.


```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion25.h"
#include <stdio.h>
#include <string.h>

void emitir_while(char lineas[][64], int max, int *n,
                  const char *cond, int *etiquetas) {

    if (lineas == NULL || n == NULL || etiquetas == NULL ||
        cond == NULL || max <= 0 || *n < 0 ||
        *n > max || *n + 4 > max || *etiquetas < 0) {
        return;
    }

    char temp[4][64];
    int inicio = *etiquetas;
    int fin = inicio + 1;
    int r;

    r = snprintf(temp[0], 64, "L%d:", inicio);
    if (r < 0 || r >= 64) return;

    r = snprintf(temp[1], 64, "IFFALSE %s GOTO L%d", cond, fin);
    if (r < 0 || r >= 64) return;

    r = snprintf(temp[2], 64, "GOTO L%d", inicio);
    if (r < 0 || r >= 64) return;

    r = snprintf(temp[3], 64, "L%d:", fin);
    if (r < 0 || r >= 64) return;

    for (int i = 0; i < 4; i++) {
        strcpy(lineas[*n], temp[i]);
        (*n)++;
    }

    *etiquetas += 2;
}

void emitir_for(char lineas[][64], int max, int *n,
                const char *inicio, const char *cond,
                const char *post, int *etiquetas) {

    if (lineas == NULL || n == NULL || etiquetas == NULL ||
        cond == NULL || max <= 0 || *n < 0 ||
        *n > max || *etiquetas < 0) {
        return;
    }

    int necesarias = 4;

    if (inicio != NULL) necesarias++;
    if (post != NULL) necesarias++;

    if (*n + necesarias > max) return;

    char temp[6][64];
    int pos = 0;

    int etiqueta_inicio = *etiquetas;
    int etiqueta_fin = etiqueta_inicio + 1;
    int r;

    if (inicio != NULL) {
        r = snprintf(temp[pos], 64, "%s", inicio);
        if (r < 0 || r >= 64) return;
        pos++;
    }

    r = snprintf(temp[pos], 64, "L%d:", etiqueta_inicio);
    if (r < 0 || r >= 64) return;
    pos++;

    r = snprintf(temp[pos], 64,
                 "IFFALSE %s GOTO L%d", cond, etiqueta_fin);
    if (r < 0 || r >= 64) return;
    pos++;

    if (post != NULL) {
        r = snprintf(temp[pos], 64, "%s", post);
        if (r < 0 || r >= 64) return;
        pos++;
    }

    r = snprintf(temp[pos], 64, "GOTO L%d", etiqueta_inicio);
    if (r < 0 || r >= 64) return;
    pos++;

    r = snprintf(temp[pos], 64, "L%d:", etiqueta_fin);
    if (r < 0 || r >= 64) return;
    pos++;

    for (int i = 0; i < pos; i++) {
        strcpy(lineas[*n], temp[i]);
        (*n)++;
    }

    *etiquetas += 2;
}
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Bucles anidados y condiciones de parada

### Salida del harness
```text
=== AUDITORIA SESION 25 - Esqueleto TAC de while y for ===

[1] while: marca de inicio       OK
[2] while: condicion             OK
[3] dos ciclos sin colision      OK
[4] for: inicializacion          OK
[5] for: actualizacion           OK
[6] for sin post (NULL)          OK

RESULTADO: 6/6 pruebas superadass
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Durante la primera compilación de la versión de IA apareció un error debido a que se había declarado una función auxiliar llamada agregar(), pero nunca se utilizaba. Como el compilador estaba configurado con -Werror, la advertencia se convirtió en un error y no permitió ejecutar las pruebas.

Para solucionarlo eliminé esa función auxiliar y mantuve la generación de instrucciones directamente dentro de emitir_while() y emitir_for(). También se agregaron validaciones de capacidad y arreglos temporales para preparar las instrucciones antes de copiarlas al arreglo principal.
> 

---
**Firma digital:** Emiliano Xooc Hau
