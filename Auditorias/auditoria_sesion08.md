# Bitácora de Requerimientos y Auditoría IA — Sesión 08
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Inferencia y Promoción de Tipos  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
En esta parte trabajé con la promoción de tipos de datos. Al principio tuve que analizar cómo comparar los tipos CHAR, INT y FLOAT para saber cuál tiene mayor rango.

Una de las dificultades fue entender cuándo una conversión puede provocar pérdida de información. También tuve que cuidar que el programa identificara correctamente los tipos inválidos.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Promoción entera y ensanchamiento |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Necesito que desarrolles una solución en lenguaje C
para una práctica de inferencia y promoción de tipos.

Debes respetar las funciones declaradas en api_sesion08.h.
Implementa las funciones promover(), hay_perdida()
y nombre_tipo().

Considera los tipos CHAR, INT, FLOAT y ERROR.
El programa debe identificar el tipo de mayor rango
y detectar cuándo una conversión puede perder información.

No agregues una función main y utiliza código claro,
ordenado y compatible con GCC.
```

---

## 3. Código Devuelto por el Modelo
```c
La inteligencia artificial proporcionó una propuesta para implementar las funciones solicitadas.

El código se utilizó en el archivo ia_sesion08_c.c. Después revisé que los nombres y las funciones coincidieran con el contrato del laboratorio.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Mezcla de tipos enteros y flotantes

### Salida del harness
```text
En esta fase se ejecutaron las pruebas automáticas para comprobar que las funciones trabajaran correctamente con diferentes combinaciones de tipos enteros y flotantes.

Se revisó especialmente que la promoción seleccionara el tipo de mayor rango y que se identificaran las conversiones que pueden perder información.
=== AUDITORIA SESION 08 - Reglas de promocion y perdida ===
Caso                               esperado:              obtenido:              resultado
[ 1] promover(CHAR,INT)                 esperado: int          obtenido: int          OK
[ 2] promover(INT,FLOAT)                esperado: float        obtenido: float        OK
[ 3] promover(FLOAT,FLOAT)              esperado: float        obtenido: float        OK
[ 4] promover(ERROR,INT)                esperado: error        obtenido: error        OK
[ 5] hay_perdida(CHAR,INT)              esperado: 1            obtenido: 1            OK
[ 6] hay_perdida(INT,CHAR)              esperado: 0            obtenido: 0            OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Durante la revisión presté atención al caso en el que uno de los tipos recibidos es TIPO_ERROR. Este caso debe tratarse de manera especial, porque no se debe realizar una promoción normal cuando existe un tipo inválido.

También revisé las conversiones entre CHAR, INT y FLOAT para evitar aceptar operaciones que puedan provocar pérdida de información.

Si se presentó algún error durante la compilación o las pruebas, se debe registrar aquí junto con la corrección realizada.
> 

---
**Firma digital:** Emiliano Xooc Hau
