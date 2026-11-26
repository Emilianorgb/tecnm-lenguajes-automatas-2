# Bitácora de Requerimientos y Auditoría IA — Sesión 16
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Firmas de Función y Parámetros  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Registro de prototipos y aridad  
En este ejercicio tuve que crear una función capaz de revisar si una llamada corresponde con la definición de una función que ya está registrada.

La parte que más atención necesitó fue diferenciar los tres resultados posibles. No es lo mismo encontrar una función con una cantidad incorrecta de argumentos que buscar una función que ni siquiera existe en el catálogo.

Para resolverlo tuve que recorrer el catálogo, comparar los nombres y después revisar la cantidad de parámetros. También fue necesario considerar los casos en los que se recibe un nombre NULL o una cantidad negativa de argumentos.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Coincidencia estricta de parámetros |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Necesito resolver una parte de un compilador en lenguaje C.
El problema consiste en revisar si una llamada a una función
está utilizando la cantidad correcta de argumentos.

Tengo una estructura llamada Funcion que contiene:
- nombre: nombre de la función.
- aridad: cantidad de parámetros que acepta.

Quiero implementar verificar_llamada(), respetando
exactamente la declaración de api_sesion16.h.

La función debe recorrer el catálogo y buscar el nombre
solicitado. Cuando lo encuentre, debe comparar su aridad
con el número de argumentos recibidos.

El resultado debe ser:
1 cuando el nombre existe y la cantidad coincide.
0 cuando existe, pero la cantidad es diferente.
-1 cuando no existe o los datos recibidos no son válidos.

Considera también:
- Catálogo NULL.
- Nombre NULL.
- Cantidad de argumentos negativa.
- Entradas del catálogo cuyo nombre sea NULL.
- Funciones que no reciben ningún parámetro.

No agregues main() ni cambies la estructura original.
Entrega el código completo, compatible con C99 y GCC,
y procura que no genere advertencias con -Wall -Wextra -Werror.
```

---

## 3. Código Devuelto por el Modelo
```c
#include "api_sesion16.h"
#include <string.h>

int verificar_llamada(
    const Funcion *catalogo,
    int total,
    const char *nombre,
    int nargs
) {
    int posicion = -1;

    if (catalogo == NULL || nombre == NULL ||
        nargs < 0 || total <= 0) {
        return -1;
    }

    for (int i = 0; i < total; i++) {
        if (catalogo[i].nombre != NULL) {
            if (strcmp(nombre, catalogo[i].nombre) == 0) {
                posicion = i;
                break;
            }
        }
    }

    if (posicion == -1) {
        return -1;
    }

    return (catalogo[posicion].aridad == nargs) ? 1 : 0;
}


```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Llamadas con número incorrecto de args

### Salida del harness
```text
=== AUDITORIA SESION 16 - Registro de prototipos y aridad ===
Caso                               esperado:              obtenido:              resultado
[ 1] suma con 3 argumentos              esperado: 1            obtenido: 1            OK
[ 2] suma con 2 argumentos              esperado: 0            obtenido: 0            OK
[ 3] suma con 4 argumentos              esperado: 0            obtenido: 0            OK
[ 4] funcion no registrada              esperado: -1           obtenido: -1           OK
[ 5] main sin argumentos                esperado: 1            obtenido: 1            OK
[ 6] nombre NULL                        esperado: -1           obtenido: -1           OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Al revisar la solución, presté atención a los registros que pudieran contener un nombre NULL. Si se utiliza strcmp() directamente con ese valor, se puede provocar un error durante la ejecución.

Para evitarlo, se agregó una condición que comprueba que el nombre del registro sea válido antes de realizar la comparación. También se verificó que un nombre NULL recibido como argumento produzca -1.

De esta manera, la búsqueda puede continuar sin intentar comparar cadenas inválidas.
> 

---
**Firma digital:** Emiliano Xooc Hau
