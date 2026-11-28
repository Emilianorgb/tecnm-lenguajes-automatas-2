# Bitácora de Requerimientos y Auditoría IA — Sesión 26
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** TAC para Llamadas a Funciones  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Instrucciones param, call y return  
Al realizar la implementación manual identifiqué que una de las dificultades fue organizar correctamente los argumentos antes de ejecutar una llamada a función. También fue necesario controlar la cantidad de instrucciones que se agregan al arreglo para evitar escribir fuera de sus límites.

Otro problema fue manejar los diferentes tipos de retorno, porque una función puede devolver un valor o simplemente terminar con una instrucción RETURN sin valor.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Convención de paso de argumentos TAC |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar dos funciones en lenguaje C99 para generar
instrucciones de código de tres direcciones (TAC).

La primera función, emitir_llamada(), debe generar instrucciones
PARAM para los argumentos recibidos y después una instrucción CALL
con el nombre de la función y la cantidad de argumentos.

Si se proporciona una variable de resultado, la llamada debe
guardar el resultado en ella. Si no se proporciona, debe generar
una llamada sin asignación.

La segunda función, emitir_return(), debe generar RETURN cuando
no exista un valor y RETURN seguido del valor cuando sí exista.

Respeta las firmas del archivo api_sesion26.h, valida los
apuntadores y la capacidad del arreglo, utiliza C99 y evita
accesos fuera de límites.

Entrega código modular y explica su complejidad temporal
y espacial.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion26.h"
#include <stdio.h>
#include <string.h>

int emitir_llamada(char lineas[][64], int max, int *n,
                   const char *funcion, const char *a1,
                   const char *a2, const char *resultado) {

    if (lineas == NULL || n == NULL || funcion == NULL ||
        funcion[0] == '\0' || max <= 0 ||
        *n < 0 || *n > max) {
        return 0;
    }

    int cantidad = 0;

    if (a1 != NULL) cantidad++;
    if (a2 != NULL) cantidad++;

    int necesarias = cantidad + 1;

    if (necesarias > max - *n) return 0;

    char temporal[3][64];
    int pos = 0;
    int r;

    if (a1 != NULL) {
        r = snprintf(temporal[pos], 64, "PARAM %s", a1);
        if (r < 0 || r >= 64) return 0;
        pos++;
    }

    if (a2 != NULL) {
        r = snprintf(temporal[pos], 64, "PARAM %s", a2);
        if (r < 0 || r >= 64) return 0;
        pos++;
    }

    if (resultado != NULL) {
        r = snprintf(temporal[pos], 64,
                     "%s = CALL %s, %d",
                     resultado, funcion, cantidad);
    } else {
        r = snprintf(temporal[pos], 64,
                     "CALL %s, %d", funcion, cantidad);
    }

    if (r < 0 || r >= 64) return 0;
    pos++;

    for (int i = 0; i < pos; i++) {
        strcpy(lineas[*n + i], temporal[i]);
    }

    *n += pos;
    return pos;
}

void emitir_return(char *dst, int cap, const char *valor) {

    if (dst == NULL || cap <= 0) return;

    if (valor == NULL) {
        snprintf(dst, (size_t)cap, "RETURN");
    } else {
        snprintf(dst, (size_t)cap, "RETURN %s", valor);
    }
}


```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Llamadas anidadas f(g(x))

### Salida del harness
```text
=== AUDITORIA SESION 26 - Llamadas, parametros y retorno ===
Caso                               esperado:              obtenido:              resultado
[ 1] PARAM x                            esperado: PARAM x      obtenido: PARAM x      OK
[ 2] PARAM y                            esperado: PARAM y      obtenido: PARAM y      OK
[ 3] CALL con dos argumentos
     esperado: _t0 = CALL f, 2
     obtenido: _t0 = CALL f, 2
     -> OK
[ 4] llamada anidada f(g(x))
     esperado: _t1 = CALL f, 1
     obtenido: _t1 = CALL f, 1
     -> OK
[ 5] CALL sin argumentos
     esperado: _t0 = CALL p, 0
     obtenido: _t0 = CALL p, 0
     -> OK
[ 6] RETURN con valor                   esperado: RETURN _t0   obtenido: RETURN _t0   OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Durante la revisión del código identifiqué que era importante validar la capacidad disponible antes de generar las instrucciones PARAM y CALL. También se debe comprobar que las cadenas no superen los 63 caracteres permitidos en cada posición del arreglo.

Otro punto importante es el manejo de las llamadas anidadas, como f(g(x)), porque primero debe generarse la llamada interna y después utilizar su resultado como argumento de la llamada externa.

La implementación utiliza un arreglo temporal para preparar las instrucciones antes de copiarlas al arreglo principal. Esto ayuda a evitar que una llamada quede parcialmente escrita cuando ocurre un error de validación.

Como mejora adicional, se deben probar los casos de cadenas demasiado largas, capacidad insuficiente y retorno sin valor.
> 

---
**Firma digital:** Emiliano Xooc Hau
