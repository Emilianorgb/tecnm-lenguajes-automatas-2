# Bitácora de Requerimientos y Auditoría IA — Sesión 18
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Arreglos y Verificación de Límites  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Cálculo de tamaño de arreglo en memoria  
Al realizar el ejercicio manualmente, tuve que identificar cuánto espacio ocupa cada tipo de dato y multiplicarlo por la cantidad de elementos del arreglo. También fue importante validar que no se recibieran cantidades negativas y comprobar que los índices estuvieran dentro del rango permitido.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Indexación entera no negativa |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.
Necesito implementar en lenguaje C dos funciones para trabajar
con arreglos y verificar sus límites.

La primera función debe calcular los bytes que ocupa un arreglo
según el tipo de dato y el número de elementos.

La segunda debe comprobar si un índice se encuentra dentro
de los límites del arreglo.

Considera los siguientes tamaños:
char = 1 byte
short = 2 bytes
int = 4 bytes
float = 4 bytes
double = 8 bytes
puntero = 8 bytes

Las funciones deben validar los parámetros recibidos,
rechazar tipos desconocidos y evitar índices negativos
o iguales o mayores que el número de elementos.

Utiliza C99, incluye las bibliotecas necesarias y respeta
las firmas declaradas en api_sesion18.h.
No agregues una función main.
Entrega código modular y explica su complejidad.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion18.h"
#include <string.h>

static int obtener_tamano(const char *tipo) {

    if (tipo == NULL) {
        return -1;
    }

    const char *tipos[] = {
        "char", "short", "int",
        "float", "double", "puntero"
    };

    const int tamanos[] = {
        1, 2, 4, 4, 8, 8
    };

    for (int i = 0; i < 6; i++) {
        if (strcmp(tipo, tipos[i]) == 0) {
            return tamanos[i];
        }
    }

    return -1;
}

long bytes_arreglo(const char *tipo, int elementos) {

    if (elementos < 0) {
        return -1;
    }

    int ancho = obtener_tamano(tipo);

    if (ancho < 0) {
        return -1;
    }

    return (long)ancho * elementos;
}

int indice_en_rango(int indice, int elementos) {

    if (elementos <= 0) {
        return 0;
    }

    return indice >= 0 && indice < elementos;
}


```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Límites estáticos y dimensiones inválidas

### Salida del harness
```text
=== AUDITORIA SESION 18 - Tamano de arreglo y limites ===
[ 1] int[10]                           esperado: 40   obtenido: 40   OK
[ 2] double[3]                         esperado: 24   obtenido: 24   OK
[ 3] int[-4]                           esperado: -1   obtenido: -1   OK
[ 4] indice 0 de 5                     esperado: 1    obtenido: 1    OK
[ 5] indice 5 de 5                     esperado: 0    obtenido: 0    OK
[ 6] indice negativo                   esperado: 0    obtenido: 0    OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Durante la revisión identifiqué que era necesario validar tanto el tipo de dato como la cantidad de elementos. Una cantidad negativa no debe producir un tamaño de memoria válido. También se debe rechazar un índice negativo o uno que sea igual al total de elementos, porque estaría fuera del arreglo.

La implementación contempla estas condiciones y utiliza comparaciones directas para evitar accesos fuera de los límites.
> 

---
**Firma digital:** Emiliano Xooc Hau
