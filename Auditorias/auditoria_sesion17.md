# Bitácora de Requerimientos y Auditoría IA — Sesión 17
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Comprobación Semántica de Retornos  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Validación de tipo de sentencia return  
Al realizar el ejercicio manualmente, la parte que más trabajo me costó fue comparar los tipos de datos y determinar cuándo una conversión era válida. También tuve que considerar los casos donde una función no devuelve ningún valor o cuando alguna ruta de ejecución se queda sin un return.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Rutas de ejecución con retorno garantizado |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Necesito implementar una función en lenguaje C para un compilador
que permita comprobar los retornos de una función.

La función debe tener exactamente esta firma:

int diagnosticar_retorno(
    const char *tipo_funcion,
    const char *tipo_expresion,
    int rutas_totales,
    int rutas_con_return
);

Debe cumplir las siguientes condiciones:

1. Devolver 0 cuando el retorno sea correcto.
2. Devolver 1 cuando el tipo de la expresión sea incompatible
   con el tipo declarado de la función.
3. Devolver 2 cuando exista una ruta de ejecución sin return.
4. Devolver -1 cuando los datos sean inválidos.
5. Una función void no debe devolver un valor.
6. Las conversiones solo se permiten cuando el tipo destino
   es igual o más ancho que el tipo de origen.
7. El tipo debe comprobarse antes que las rutas.
8. Debe detectar cero rutas y cantidades incoherentes.

Utiliza C11, incluye las bibliotecas necesarias y respeta
la firma original. No agregues una función main.


```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion17.h"
#include <string.h>

static int rango_tipo(const char *tipo) {
    if (tipo == NULL) {
        return -1;
    }

    if (strcmp(tipo, "char") == 0) {
        return 1;
    } else if (strcmp(tipo, "int") == 0) {
        return 2;
    } else if (strcmp(tipo, "float") == 0) {
        return 3;
    } else if (strcmp(tipo, "double") == 0) {
        return 4;
    } else if (strcmp(tipo, "void") == 0) {
        return 0;
    }

    return -1;
}

int diagnosticar_retorno(
    const char *tipo_funcion,
    const char *tipo_expresion,
    int rutas_totales,
    int rutas_con_return
) {
    int tipo_destino;
    int tipo_origen;

    if (tipo_funcion == NULL || tipo_expresion == NULL) {
        return -1;
    }

    if (rutas_totales <= 0 ||
        rutas_con_return < 0 ||
        rutas_con_return > rutas_totales) {
        return -1;
    }

    tipo_destino = rango_tipo(tipo_funcion);
    tipo_origen = rango_tipo(tipo_expresion);

    if (tipo_destino < 0 || tipo_origen < 0) {
        return -1;
    }

    /* Primero se comprueba la compatibilidad de tipos. */
    if (tipo_destino == 0 || tipo_origen == 0) {
        if (tipo_destino != tipo_origen) {
            return 1;
        }
        return 0;
    }

    if (tipo_destino < tipo_origen) {
        return 1;
    }

    /* Después se revisa que todas las rutas tengan return. */
    if (rutas_con_return < rutas_totales) {
        return 2;
    }

    return 0;
}
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Funciones sin retorno o retornos mixtos

### Salida del harness
```text
=== AUDITORIA SESION 17 - Validacion de retornos y rutas ===
Caso                               esperado:              obtenido:              resultado
[ 1] int con int y dos rutas            esperado: 0            obtenido: 0            OK
[ 2] void devuelve valor                esperado: 1            obtenido: 1            OK
[ 3] ruta sin retorno                   esperado: 2            obtenido: 2            OK
[ 4] double acepta int                  esperado: 0            obtenido: 0            OK
[ 5] int no acepta double               esperado: 1            obtenido: 1            OK
[ 6] cero rutas de ejecucion            esperado: -1           obtenido: -1           OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Durante la revisión identifiqué que era importante comprobar primero la compatibilidad de los tipos y después verificar las rutas de ejecución. Si se revisan primero las rutas, se puede informar un error de retorno faltante cuando en realidad el problema es que se está devolviendo un tipo incompatible.

También se deben validar los valores NULL y los conteos de rutas para evitar resultados incorrectos. Estas condiciones quedaron contempladas en la implementación.
> 

---
**Firma digital:** Emiliano Xooc Hau
