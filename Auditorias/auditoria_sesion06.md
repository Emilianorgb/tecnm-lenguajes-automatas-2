# Bitácora de Requerimientos y Auditoría IA — Sesión 06
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Sistema de Tipos Primitivos  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau

**Matrícula:** 24531402

**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Chequeo de compatibilidad de tipos  
En esta actividad trabajé con una regla que utilizan los compiladores para saber si un dato puede asignarse a una variable de otro tipo.

La parte que tuve que analizar fue el orden de los tipos. En este ejercicio se maneja la jerarquía CHAR < INT < FLOAT, por lo que se permite asignar un tipo pequeño a uno de mayor capacidad, pero no al contrario.

Para resolverlo utilicé una comparación entre los valores de los tipos y agregué una condición para rechazar cualquier operación donde apareciera TIPO_ERROR. También implementé una función para obtener el nombre de cada tipo.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Matriz de compatibilidad estática |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Estoy trabajando en la parte semántica de un compilador
y necesito implementar una pequeña tabla de compatibilidad
para los tipos primitivos.

En mi proyecto tengo definidos estos tipos:
TIPO_ERROR, TIPO_CHAR, TIPO_INT y TIPO_FLOAT.

La jerarquía que estoy utilizando es:
CHAR < INT < FLOAT.

Necesito dos funciones:

- compatible(destino, origen): indica si un valor de cierto
  tipo puede asignarse a una variable de otro tipo.
- nombre_tipo(t): devuelve el nombre correspondiente al tipo.

La regla principal es que se permita asignar un tipo a otro
del mismo rango o de mayor capacidad. Si el destino es más
pequeño, debe rechazarse.

También considera que TIPO_ERROR nunca debe ser compatible
y que cada tipo debe devolver su nombre correcto.

Respeta las declaraciones de api_sesion06.h, no cambies
los parámetros y no agregues main().

Quiero una solución sencilla en C que pueda compilarse
con GCC sin generar advertencias.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA presentó una solución que utiliza switch para revisar cada tipo de origen.

En lugar de comparar directamente los valores numéricos de los tipos, establece las combinaciones que sí están permitidas. Por ejemplo, cuando el origen es TIPO_CHAR, permite asignarlo a CHAR, INT o FLOAT. Cuando el origen es TIPO_FLOAT, solamente permite asignarlo a otro FLOAT.

La segunda función también utiliza switch para devolver el nombre de cada tipo. Si recibe un valor que no reconoce, devuelve "error".

Funciones implementadas:

compatible(Tipo destino, Tipo origen)

nombre_tipo(Tipo t)

Esta solución permite identificar de forma clara qué asignaciones están permitidas y cuáles deben rechazarse.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Rechazo de asignaciones incompatibles

### Salida del harness
```text
=== AUDITORIA SESION 06 - Tabla de compatibilidad de tipos ===
Caso                               esperado:              obtenido:              resultado
[ 1] compatible(INT,INT)                esperado: 1            obtenido: 1            OK
[ 2] compatible(FLOAT,INT)              esperado: 1            obtenido: 1            OK
[ 3] compatible(INT,FLOAT)              esperado: 0            obtenido: 0            OK
[ 4] compatible(INT,ERROR)              esperado: 0            obtenido: 0            OK
[ 5] nombre_tipo(INT)                   esperado: int          obtenido: int          OK
[ 6] nombre_tipo(ERROR)                 esperado: error        obtenido: error        OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
*¿Qué caso borde o problema omitió la IA y cómo lo solucionaste?*
> 

---
**Firma digital:** Emiliano Xooc Hau Ignacio Zaragoza
