# Bitácora de Requerimientos y Auditoría IA — Sesión 05
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Recorridos del AST y Notación Polaca  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Impresión en Postorden / RPN  
En esta actividad tuve que encontrar la manera de recorrer un árbol sintáctico y guardar los resultados en una cadena de texto. Lo que se me hizo más interesante fue que no se debía imprimir directamente en pantalla, sino escribir todo dentro de un buffer.

Para conseguirlo tuve que utilizar la recursividad. Primero se visita el hijo izquierdo, después el derecho y al final se agrega el operador que corresponde al nodo principal.

También tuve que cuidar que los elementos quedaran separados por un solo espacio y que no se sobrepasara el tamaño del buffer. Esto es importante porque, si no se controla la capacidad, se puede escribir fuera del espacio reservado.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Invariantes de recorrido recursivo |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Estoy trabajando con árboles sintácticos y necesito convertir
su estructura a notación polaca inversa.

Quiero que me ayudes a implementar la función postorden()
en lenguaje C, respetando la estructura ASTNode y la firma
que aparece en api_sesion05.h.

La función debe recorrer cada nodo siguiendo este orden:
primero el izquierdo, luego el derecho y al final la raíz.

Los números deben escribirse con su valor y los operadores
deben aparecer después de sus dos operandos.

El resultado tiene que guardarse en el buffer que recibe
la función. No quiero que utilices printf.

También necesito que tengas cuidado con estos puntos:
- Si el árbol es NULL, el resultado debe quedar vacío.
- Los elementos deben separarse con un solo espacio.
- No debe quedar un espacio al final.
- El buffer siempre debe terminar correctamente con '\0'.
- Respeta el límite indicado por cap.
- No modifiques la estructura ni la firma de la función.

Utiliza recursividad y entrega una solución compatible
con C99, sin agregar main().
```

---

## 3. Código Devuelto por el Modelo
```c
La IA propuso dividir el trabajo en dos funciones para mantener el recorrido organizado.

La primera función auxiliar, agregar_token(), se encarga de colocar cada número u operador en el buffer, revisando cuánto espacio queda disponible.

La segunda, recorrer(), realiza el recorrido recursivo del árbol. Cuando encuentra un nodo numérico, guarda su valor. Cuando encuentra un nodo de operación, visita primero sus dos hijos y después agrega el operador.

Por último, postorden() limpia el buffer al comenzar y llama a la función auxiliar para realizar todo el recorrido.

La solución utiliza estas funciones:

agregar_token()

recorrer()

postorden()
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Validación contra desbordamiento de pila

### Salida del harness
```text
=== AUDITORIA SESION 05 - Recorrido postorden y RPN ===
Caso                               esperado:              obtenido:              resultado
[ 1] hoja 42                            esperado: 42           obtenido: 42           OK
[ 2] 3+(5*2)                            esperado: 3 5 2 * +    obtenido: 3 5 2 * +    OK
[ 3] arbol NULL                         esperado:              obtenido:              OK
[ 4] (1+2)*(3+4)
     esperado: 1 2 + 3 4 + *
     obtenido: 1 2 + 3 4 + *
     -> OK
[ 5] 8-3                                esperado: 8 3 -        obtenido: 8 3 -        OK

RESULTADO: 5/5 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
*¿Qué caso borde o problema omitió la IA y cómo lo solucionaste?*
La IA omitió considerar el caso en que el árbol está vacío (NULL). Lo solucioné agregando una condición para verificar si el nodo es nulo antes de recorrerlo. Si el árbol no existe, la función deja el buffer como una cadena vacía, evitando errores y cumpliendo con lo que pide el auditor.

---
**Firma digital:** Emiliano Xooc Hau Ignacio Zaragoza
