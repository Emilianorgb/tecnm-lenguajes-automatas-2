# Bitácora de Requerimientos y Auditoría IA — Sesión 12
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Atributos de Símbolos y Memoria  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Estructura de registro de símbolos  
Al realizar esta actividad, una de las dificultades fue entender cómo se calcula el espacio que ocupa cada tipo de dato en memoria. No todos los tipos necesitan la misma cantidad de bytes, por lo que fue necesario identificar su tamaño antes de asignar un desplazamiento.

También tuve que considerar la alineación de memoria. Por ejemplo, si el cursor se encuentra en la posición 4 y se quiere guardar un dato de tipo double, es necesario avanzar hasta la posición 8 para respetar su alineación.

Para resolverlo utilicé operaciones de módulo, que permiten calcular cuánto espacio se necesita avanzar antes de asignar el siguiente offset.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Cálculo de desplazamientos y alineación |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar en lenguaje C funciones para calcular
el tamaño de los tipos de datos y asignar desplazamientos
en memoria.

La implementación debe:
- Reconocer los tipos char, short, int, float, double y puntero.
- Devolver el tamaño correspondiente en bytes.
- Calcular el offset de cada símbolo.
- Respetar la alineación según el tamaño del tipo.
- Validar los parámetros recibidos.
- Detectar tipos desconocidos.
- Evitar desbordamientos de enteros.
- Respetar la API proporcionada.
- No incluir una función main().
- Compilar con GCC usando -Wall -Wextra -Werror.

Entrega código modular y explica brevemente su funcionamiento.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA propuso una solución que utiliza dos funciones principales:

int ancho_de_tipo(const char *tipo);

int asignar_offset(Simbolo *simbolo, int cursor);

La primera función identifica el tipo de dato y devuelve el espacio que necesita en bytes.

La segunda calcula el desplazamiento correspondiente, tomando en cuenta el cursor actual y la alineación necesaria para almacenar el siguiente símbolo.

El código completo se encuentra en el archivo ia_sesion12_c.c.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Alineación de tipos y tamaños en bytes

### Salida del harness
```text
Pruebas ejecutadas: 6 casos relacionados con tamaños de tipos y alineación de memoria.

Casos revisados

Prueba

Descripción

Resultado esperado

1

Obtener el tamaño de int.

4 bytes

2

Obtener el tamaño de double.

8 bytes

3

Asignar un int desde el cursor 0.

Offset final 4

4

Asignar char y después int.

Offset de int: 4

5

Asignar double desde el cursor 4.

Offset: 8

6

Intentar asignar un registro NULL.

Error: -1
=== AUDITORIA SESION 12 - Registro de simbolo y offsets alineados ===
Caso                               esperado:              obtenido:              resultado
[ 1] ancho_de_tipo("int")               esperado: 4            obtenido: 4            OK
[ 2] ancho_de_tipo("double")            esperado: 8            obtenido: 8            OK
[ 3] int en cursor 0                    esperado: 4            obtenido: 4            OK
[ 4] char e int: offset de b            esperado: 4            obtenido: 4            OK
[ 5] double desde cursor 4              esperado: 8            obtenido: 8            OK
[ 6] registro NULL                      esperado: -1           obtenido: -1           OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Un aspecto importante de esta actividad fue considerar que el siguiente símbolo no siempre puede colocarse inmediatamente después del anterior.

Por ejemplo, después de almacenar un char, el siguiente int debe comenzar en una posición múltiplo de 4. De la misma manera, un double debe comenzar en una posición múltiplo de 8.

Para solucionar esto se utilizó el cálculo del espacio de relleno (padding) mediante el operador módulo.

También se consideró la validación de tipos desconocidos y de valores que podrían provocar un desbordamiento al calcular el siguiente desplazamiento.
> 

---
**Firma digital:** Emiliano Xooc Hau
