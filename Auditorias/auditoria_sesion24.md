# Bitácora de Requerimientos y Auditoría IA — Sesión 24
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Control de Flujo: Sentencia if-else  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Saltos condicionales y evaluación booleana  
Al realizar la implementación manual identifiqué que una de las principales dificultades es controlar correctamente los saltos condicionales y el espacio disponible para almacenar las instrucciones. También es necesario revisar los valores de los argumentos para evitar errores cuando se reciben apuntadores nulos o cuando se intenta generar más instrucciones de las permitidas.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Cortocircuito lógico en expresiones |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar una función en lenguaje C99 para generar
instrucciones de salto condicional.

La función debe recibir una matriz de instrucciones, su capacidad,
dos operandos, un operador lógico y una etiqueta de destino.

Debe reconocer los operadores AND (&) y OR (|), generar las
instrucciones correspondientes utilizando IFFALSE e IFTRUE,
respetar la capacidad máxima de la matriz y validar los argumentos.

Si algún argumento obligatorio es NULL o el operador no es válido,
debe evitar generar instrucciones incorrectas.

El código debe ser modular, utilizar únicamente bibliotecas estándar
y explicar su complejidad temporal y espacial.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion24.h"
#include <stdio.h>
#include <string.h>

int emitir_condicion(char lineas[][64], int max,
                     const char *a, const char *b,
                     char op, const char *etiqueta) {

    if (lineas == NULL || max <= 0 ||
        a == NULL || etiqueta == NULL ||
        a[0] == '\0' || etiqueta[0] == '\0') {
        return 0;
    }

    const char *salto;

    if (op == '&') {
        salto = "IFFALSE";
    } else if (op == '|') {
        salto = "IFTRUE";
    } else {
        return 0;
    }

    int total = 0;
    int longitud;

    longitud = snprintf(lineas[total], 64,
                        "%s %s GOTO %s",
                        salto, a, etiqueta);

    if (longitud < 0 || longitud >= 64) {
        lineas[total][0] = '\0';
        return 0;
    }

    total++;

    if (b != NULL) {
        if (total >= max || b[0] == '\0') {
            return total;
        }

        longitud = snprintf(lineas[total], 64,
                            "%s %s GOTO %s",
                            salto, b, etiqueta);

        if (longitud < 0 || longitud >= 64) {
            lineas[total][0] = '\0';
            return total;
        }

        total++;
    }

    return total;
}
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Condiciones compuestas con AND y OR

### Salida del harness
```text
=== AUDITORIA SESION 24 - Saltos condicionales con cortocircuito ===
Caso                               esperado:              obtenido:              resultado
[ 1] a && b (primer salto)
     esperado: IFFALSE a GOTO L9
     obtenido: IFFALSE a GOTO L9
     -> OK
[ 2] a && b (segundo salto)
     esperado: IFFALSE b GOTO L9
     obtenido: IFFALSE b GOTO L9
     -> OK
[ 3] a && b (dos saltos)                esperado: 2            obtenido: 2            OK
[ 4] a || b (primer salto)
     esperado: IFTRUE a GOTO L9
     obtenido: IFTRUE a GOTO L9
     -> OK
[ 5] a || b (segundo salto)
     esperado: IFTRUE b GOTO L9
     obtenido: IFTRUE b GOTO L9
     -> OK
[ 6] condicion simple (b NULL)
     esperado: IFFALSE a GOTO L0
     obtenido: IFFALSE a GOTO L0
     -> OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Al revisar el código generado por la IA encontré que se deben considerar algunos casos adicionales. Por ejemplo, cuando la capacidad máxima es uno, cuando el segundo operando está vacío o cuando el texto de una instrucción supera los 63 caracteres disponibles.

También es importante comprobar que la generación de instrucciones represente correctamente el cortocircuito lógico de AND y OR. La implementación debe verificarse con el harness y con pruebas adicionales para confirmar que los saltos se producen en el orden correcto.

Como mejora, se puede validar cada instrucción antes de almacenarla y comprobar que no se escriba fuera de los límites de la matriz.
> 

---
**Firma digital:** Emiliano Xooc Hau
