# Bitácora de Requerimientos y Auditoría IA — Sesión 22
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Generación de TAC para Expresiones  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Traductor de nodos AST a TAC  
Al realizar el código manualmente, la principal dificultad fue organizar el recorrido del árbol para que primero se procesaran los hijos y después el operador. También tuve que controlar la numeración de los temporales para que no se repitieran y asegurar que no se escribieran más líneas de las permitidas.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Conservación de precedencia de operadores |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar en C una función llamada generar_tac que
convierta un árbol de sintaxis abstracta (AST) en instrucciones
de código de tres direcciones.

La función debe tener exactamente esta firma:

int generar_tac(const Nodo *raiz, char lineas[][64], int max);

Utiliza la estructura Nodo definida en api_sesion22.h.

Requisitos:
1. Recorrer el árbol en postorden.
2. Procesar primero los nodos hijos y después el operador.
3. Generar una instrucción TAC por cada operador binario.
4. Utilizar la función nuevo_temporal para obtener nombres como
   _t0, _t1 y _t2.
5. Las hojas deben devolver su valor sin generar instrucciones.
6. No escribir más de max líneas.
7. No escribir más de 63 caracteres por línea.
8. Respetar exactamente la firma y no incluir main().

Entrega únicamente el código modular en C99 y su análisis
de complejidad.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion22.h"
#include <stdio.h>

typedef struct {
    char nombres[64][16];
    int siguiente;
} Generador;

static const char *crear_temporal(Generador *g) {
    if (g->siguiente >= 64) {
        return NULL;
    }

    int indice = g->siguiente;

    int escrito = snprintf(
        g->nombres[indice],
        sizeof g->nombres[indice],
        "_t%d",
        indice
    );

    if (escrito < 0 ||
        escrito >= (int)sizeof g->nombres[indice]) {
        return NULL;
    }

    g->siguiente++;
    return g->nombres[indice];
}

static const char *generar(
    const Nodo *nodo,
    char lineas[][64],
    int max,
    int *cantidad,
    Generador *g
) {
    if (nodo == NULL) {
        return NULL;
    }

    if (nodo->tipo == 'H') {
        return nodo->valor;
    }

    if (nodo->tipo != 'B' ||
        nodo->izq == NULL ||
        nodo->der == NULL) {
        return NULL;
    }

    const char *izq = generar(
        nodo->izq, lineas, max, cantidad, g
    );

    const char *der = generar(
        nodo->der, lineas, max, cantidad, g
    );

    if (izq == NULL || der == NULL) {
        return NULL;
    }

    if (*cantidad >= max) {
        return NULL;
    }

    const char *temporal = crear_temporal(g);

    if (temporal == NULL) {
        return NULL;
    }

    int escrito = snprintf(
        lineas[*cantidad],
        64,
        "%s = %s %c %s",
        temporal,
        izq,
        nodo->op,
        der
    );

    if (escrito < 0 || escrito >= 64) {
        return NULL;
    }

    (*cantidad)++;

    return temporal;
}

int generar_tac(const Nodo *raiz, char lineas[][64], int max) {
    if (raiz == NULL || lineas == NULL || max <= 0) {
        return 0;
    }

    Generador generador = {0};
    int cantidad = 0;

    generar(raiz, lineas, max, &cantidad, &generador);

    return cantidad;
}
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Expresiones anidadas con paréntesis

### Salida del harness
```text
=== AUDITORIA SESION 22 - Traductor de AST a TAC con precedencia ===
Caso                               esperado:              obtenido:              resultado
[ 1] a + b * c                          esperado: _t0 = b * c  obtenido: _t0 = b * c  OK
[ 2] a + b * c (2a linea)
     esperado: _t1 = a + _t0
     obtenido: _t1 = a + _t0
     -> OK
[ 3] (a + b) * c
     esperado: _t1 = _t0 * c
     obtenido: _t1 = _t0 * c
     -> OK
[ 4] x * (y - z) + w
     esperado: _t2 = _t1 + w
     obtenido: _t2 = _t1 + w
     -> OK
[ 5] hoja sin operaciones               esperado: 0            obtenido: 0            OK
[ 6] (a + b) * (c - d)
     esperado: _t2 = _t0 * _t1
     obtenido: _t2 = _t0 * _t1
     -> OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Un aspecto importante que se debe revisar es el límite de temporales y el tamaño de cada instrucción. La implementación utiliza un arreglo de 64 temporales y snprintf para controlar el tamaño de las cadenas.

También se debe verificar que, cuando un nodo está incompleto o el árbol tiene una referencia nula, no se intente generar una operación inválida. Estos casos requieren atención porque pueden provocar errores durante el recorrido recursivo.
> 

---
**Firma digital:** Emiliano Xooc Hau
