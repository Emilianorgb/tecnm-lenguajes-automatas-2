# Bitácora de Requerimientos y Auditoría IA — Sesión 20
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Hito 2: Analizador Semántico y Scopes  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Integración de Tabla de Símbolos y AST  
Al realizar el ejercicio manualmente, una de las dificultades fue recorrer correctamente los ámbitos relacionados mediante el campo padre. También tuve que considerar que un nombre puede aparecer en varios niveles. Para resolverlo, se debe buscar primero en el ámbito actual y después continuar hacia los ámbitos superiores.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Contrato de Validación Semántica Integral |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar dos funciones en C para resolver nombres
y contar los símbolos visibles dentro de una cadena de ámbitos.

La primera función debe llamarse profundidad_de y recibir:
const Ambito *actual y const char *nombre.

Debe devolver:
- 0 si el nombre está en el ámbito actual.
- 1 si está en el ámbito padre.
- 2 si está dos niveles arriba, y así sucesivamente.
- -1 si el nombre no existe.
- -2 si alguno de sus argumentos es NULL.

La segunda función debe llamarse contar_visibles y recibir
un puntero al ámbito actual.

Debe contar cada nombre una sola vez, aunque aparezca
en diferentes niveles de la cadena.
El ámbito más interno debe tener prioridad cuando existan
nombres repetidos (shadowing).

Respeta exactamente las firmas de api_sesion20.h.
Utiliza C99, incluye las bibliotecas necesarias y no agregues
una función main.

Entrega código modular y explica su complejidad.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion20.h"
#include <string.h>

static int ambito_valido(const Ambito *ambito) {
    return ambito != NULL &&
           ambito->total >= 0 &&
           ambito->total <= AMBITO_MAX;
}

int profundidad_de(const Ambito *actual, const char *nombre) {
    if (actual == NULL || nombre == NULL) {
        return -2;
    }

    int nivel = 0;

    for (const Ambito *a = actual; a != NULL; a = a->padre) {
        if (!ambito_valido(a)) {
            return -1;
        }

        for (int i = 0; i < a->total; i++) {
            const char *simbolo = a->simbolos[i];

            if (simbolo != NULL && strcmp(simbolo, nombre) == 0) {
                return nivel;
            }
        }

        nivel++;
    }

    return -1;
}

int contar_visibles(const Ambito *actual) {
    if (actual == NULL) {
        return -2;
    }

    int total_visible = 0;

    for (const Ambito *a = actual; a != NULL; a = a->padre) {
        if (!ambito_valido(a)) {
            return -1;
        }

        for (int i = 0; i < a->total; i++) {
            const char *nombre = a->simbolos[i];

            if (nombre == NULL) {
                continue;
            }

            int repetido = 0;

            for (const Ambito *interno = actual;
                 interno != a;
                 interno = interno->padre) {

                if (!ambito_valido(interno)) {
                    return -1;
                }

                for (int j = 0; j < interno->total; j++) {
                    if (interno->simbolos[j] != NULL &&
                        strcmp(interno->simbolos[j], nombre) == 0) {
                        repetido = 1;
                        break;
                    }
                }

                if (repetido) {
                    break;
                }
            }

            for (int j = 0; j < i && !repetido; j++) {
                if (a->simbolos[j] != NULL &&
                    strcmp(a->simbolos[j], nombre) == 0) {
                    repetido = 1;
                }
            }

            if (!repetido) {
                total_visible++;
            }
        }
    }

    return total_visible;
}
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Casos complejos de shadowing y ámbito

### Salida del harness
```text
=== AUDITORIA SESION 20 - Resolucion de nombres y visibilidad ===
Caso                               esperado:              obtenido:              resultado
[ 1] nombre en el ambito actual         esperado: 0            obtenido: 0            OK
[ 2] nombre dos niveles arriba          esperado: 2            obtenido: 2            OK
[ 3] shadowing gana el interno          esperado: 0            obtenido: 0            OK
[ 4] nombre no visible                  esperado: -1           obtenido: -1           OK
[ 5] visibles sin repetir               esperado: 3            obtenido: 3            OK
[ 6] ambito NULL                        esperado: -2           obtenido: -2           OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Durante la revisión observé que es importante respetar el orden de búsqueda de los ámbitos. Si un nombre está declarado tanto en el ámbito actual como en el global, debe tener prioridad el que se encuentra más cerca. También se debe evitar contar dos veces el mismo símbolo.

La implementación contempla estas condiciones y valida los argumentos NULL. Como limitación adicional, el código no detecta ciclos en los enlaces padre; ese escenario no forma parte de los casos contemplados por el contrato ni por el harness de esta sesión.
> 

---
**Firma digital:** Emiliano Xooc Hau
