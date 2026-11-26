# Bitácora de Requerimientos y Auditoría IA — Sesión 19
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Estructuras (struct) y Miembros  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Offsets de miembros en estructuras  
Al desarrollar el código manualmente, la parte más complicada fue calcular la posición de cada miembro dentro de una estructura. No basta con sumar el tamaño de los campos, porque también se debe considerar la alineación de memoria. Por eso tuve que revisar cómo se agrega el padding para que cada campo ocupe una posición adecuada.

> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Alineación de memoria por palabras |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar dos funciones en C para calcular los offsets
de los miembros de una estructura y su tamaño total.

Utiliza la estructura Campo, que contiene el nombre y el tipo
de cada miembro.

La función offset_campo debe recibir un arreglo de campos,
su cantidad y el nombre del miembro que se desea buscar.
Debe devolver su posición en memoria o -1 si no existe.

La función tamano_struct debe calcular el tamaño total
de la estructura, incluyendo la alineación de los campos
y el padding final.

Considera los siguientes tamaños:
char = 1 byte
short = 2 bytes
int = 4 bytes
float = 4 bytes
double = 8 bytes
puntero = 8 bytes

Valida los punteros, los tipos desconocidos y las cantidades
inválidas. Respeta exactamente las funciones declaradas
en api_sesion19.h.

Utiliza C99 y no agregues una función main.
Entrega código modular y explica la complejidad.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion19.h"
#include <string.h>

static int ancho_tipo(const char *tipo) {
    if (tipo == NULL) return -1;

    const char *nombres[] = {
        "char", "short", "int", "float", "double", "puntero"
    };

    const int anchos[] = {
        1, 2, 4, 4, 8, 8
    };

    for (int i = 0; i < 6; i++) {
        if (strcmp(tipo, nombres[i]) == 0) {
            return anchos[i];
        }
    }

    return -1;
}

static int ajustar_alineacion(int posicion, int alineacion) {
    int resto = posicion % alineacion;

    return resto == 0
        ? posicion
        : posicion + alineacion - resto;
}

int offset_campo(const Campo *campos, int total, const char *nombre) {
    int posicion = 0;

    if (campos == NULL || nombre == NULL || total <= 0) {
        return -1;
    }

    for (int i = 0; i < total; i++) {
        if (campos[i].nombre == NULL) {
            return -1;
        }

        int ancho = ancho_tipo(campos[i].tipo);

        if (ancho < 0) {
            return -1;
        }

        posicion = ajustar_alineacion(posicion, ancho);

        if (strcmp(nombre, campos[i].nombre) == 0) {
            return posicion;
        }

        posicion += ancho;
    }

    return -1;
}

int tamano_struct(const Campo *campos, int total) {
    int posicion = 0;
    int alineacion_maxima = 0;

    if (total < 0 || (total > 0 && campos == NULL)) {
        return -1;
    }

    for (int i = 0; i < total; i++) {
        int ancho = ancho_tipo(campos[i].tipo);

        if (ancho < 0) {
            return -1;
        }

        posicion = ajustar_alineacion(posicion, ancho);
        posicion += ancho;

        if (ancho > alineacion_maxima) {
            alineacion_maxima = ancho;
        }
    }

    if (total == 0) {
        return 0;
    }

    return ajustar_alineacion(posicion, alineacion_maxima);
}


```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Acceso a miembros inexistentes

### Salida del harness
```text
=== AUDITORIA SESION 19 - Offsets de miembros y tamano de struct ===
[ 1] struct char e int: b               esperado: 4            obtenido: 4            OK
[ 2] struct de tres campos: c           esperado: 8            obtenido: 8            OK
[ 3] tamano total con padding           esperado: 12           obtenido: 12           OK
[ 4] double seguido de char             esperado: 16           obtenido: 16           OK
[ 5] miembro inexistente                esperado: -1           obtenido: -1           OK
[ 6] struct sin campos                  esperado: 0            obtenido: 0            OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Durante la revisión me enfoqué en el caso de los miembros inexistentes y en las estructuras que no contienen campos. También comprobé que el cálculo de los offsets considere la alineación y no solamente la suma de los tamaños.

La implementación devuelve -1 cuando el miembro no existe o los datos son inválidos, y devuelve 0 para una estructura sin campos. Estas condiciones ayudan a evitar resultados incorrectos durante el cálculo.
> 

---
**Firma digital:** Emiliano Xooc Hau
