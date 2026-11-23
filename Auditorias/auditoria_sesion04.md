# Bitácora de Requerimientos y Auditoría IA — Sesión 04
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Anatomía de un Árbol Sintáctico (AST)  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Estructura de nodo binario (ASTNode)  
En esta práctica comencé a trabajar con una estructura diferente a las listas enlazadas. Ahora tenía que crear nodos que representaran números y operaciones matemáticas, conectándolos entre sí para formar un árbol.

Lo que más tuve que cuidar fue asignar correctamente los hijos izquierdo y derecho de cada nodo. También fue necesario distinguir cuándo un nodo representa un número y cuándo representa una operación.

Otro detalle importante fue reservar memoria para cada nodo y comprobar que la función no intentara evaluar un árbol que no existe. Esto último es necesario para evitar errores al utilizar los punteros.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Gramática E -> E + T | T con tipos de nodo |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Estoy realizando un ejercicio donde necesito representar
operaciones matemáticas mediante un árbol sintáctico (AST).

Ayúdame a implementar en C las funciones que aparecen
en api_sesion04.h.

El programa debe permitir crear dos clases de nodos:
- Nodos que almacenen números enteros.
- Nodos que representen operaciones con dos hijos.

Necesito que las funciones permitan construir el árbol
y después obtener el resultado recorriéndolo de forma recursiva.

Las operaciones que se deben reconocer son:
suma (+), resta (-) y multiplicación (*).

Hay ciertas condiciones que debes respetar:
1. Reserva memoria para cada nodo con malloc.
2. Asigna correctamente el tipo y los valores.
3. Conserva el orden de los hijos izquierdo y derecho.
4. Si evaluar recibe NULL, debe regresar -1.
5. No agregues main ni cambies las firmas originales.

Entrega el código completo de las funciones, utilizando
las estructuras que ya están definidas en la cabecera.
```

---

## 3. Código Devuelto por el Modelo
```c
La solución de la IA utiliza tres funciones principales:

crear_numero(): reserva memoria y guarda el valor entero dentro de un nodo.

crear_binario(): crea un nodo para una operación y conecta sus dos hijos.

evaluar(): recorre el árbol mediante llamadas recursivas y realiza la operación correspondiente.

Por ejemplo, para evaluar la expresión 3+5*2, primero se obtiene el resultado de la multiplicación y después se suma el número 3. El resultado es 13.

También se incluye una validación para que evaluar() devuelva -1 cuando recibe un puntero NULL.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Árbol vacío y evaluación de nodo raíz

### Salida del harness
```text
=== AUDITORIA SESION 04 - Nodo binario de AST ===
Caso                               esperado:              obtenido:              resultado
[ 1] evaluar(nodo 42)                   esperado: 42           obtenido: 42           OK
[ 2] evaluar(3+5*2)                     esperado: 13           obtenido: 13           OK
[ 3] hijo izquierdo de (* 5 2)          esperado: 5            obtenido: 5            OK
[ 4] operador guardado                  esperado: *            obtenido: *            OK
[ 5] evaluar(NULL)                      esperado: -1           obtenido: -1           OK
[ 6] evaluar(10-4)                      esperado: 6            obtenido: 6            OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
*¿Qué caso borde o problema omitió la IA y cómo lo solucionaste?*
La IA omitió considerar el caso de un árbol nulo (NULL). Lo solucioné agregando una condición al inicio de la función evaluar() para que devolviera -1 cuando no recibiera un nodo válido, evitando acceder a memoria inválida.

---
**Firma digital:** Emiliano Xooc Hau Ignacio Zaragoza
