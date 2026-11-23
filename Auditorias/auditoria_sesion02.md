# Bitácora de Requerimientos y Auditoría IA — Sesión 02
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Gestión en GitHub Web y Nodos Dinámicos  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau 
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Lista enlazada de tokens en Heap  
En esta práctica tuve que crear una lista que pudiera guardar tokens sin saber desde el principio cuántos elementos iba a necesitar. Lo que más trabajo me dio fue entender cómo agregar un nuevo nodo al final sin perder la conexión con los anteriores.

También tuve que utilizar malloc para reservar memoria y revisar que la reserva se realizara correctamente. Otra parte importante fue recorrer la lista hasta encontrar el último nodo y dejar su puntero siguiente en NULL.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Gestión de memoria dinámica C99/Rust |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Estoy trabajando en una práctica de Lenguajes y Autómatas II
y necesito implementar una lista enlazada para almacenar tokens.

Quiero que me ayudes a desarrollar las siguientes funciones en C:

1. agregar_token: recibe una lista y un lexema, crea un nuevo
   nodo y lo coloca al final.
2. contar_tokens: recorre la lista y devuelve cuántos nodos tiene.
3. liberar_lista: libera todos los nodos reservados dinámicamente.

Cada nodo debe guardar un lexema de máximo 15 caracteres
más el carácter final '\0', y un puntero al siguiente nodo.

Ten cuidado con estos detalles:
- Utiliza malloc para crear los nodos.
- Comprueba si malloc devuelve NULL.
- No pierdas la cabeza de la lista al agregar elementos.
- El último nodo debe apuntar a NULL.
- Las funciones deben trabajar con una lista vacía.
- Liberar una lista NULL no debe provocar errores.
- Si el lexema es NULL, conserva la lista original.

Respeta exactamente las funciones declaradas en api_sesion02.h.
No agregues main() y utiliza código compatible con C99.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA entregó una solución que utiliza memoria dinámica para crear cada nodo. Primero comprueba que el lexema sea válido, después reserva espacio con malloc y copia el texto al campo correspondiente.

Cuando la lista ya tiene elementos, recorre los nodos utilizando siguiente hasta llegar al último. Ahí conecta el nuevo elemento.

Las otras dos funciones tienen tareas más directas: contar_tokens recorre la lista y aumenta un contador, mientras que liberar_lista va guardando la dirección del siguiente nodo antes de liberar el actual con free.

Funciones implementadas:

agregar_token()

contar_tokens()

liberar_lista()
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Prevención de Use-After-Free y cadenas nulas

### Salida del harness
```text
=== AUDITORIA SESION 02 - Lista enlazada de tokens en heap ===
Caso                               esperado:              obtenido:              resultado
[ 1] agregar_token(NULL,"if")           esperado: if           obtenido: if           OK
[ 2] contar_tokens(3 tokens)            esperado: 3            obtenido: 3            OK
[ 3] orden: segundo token               esperado: dos          obtenido: dos          OK
[ 4] ultimo->siguiente == NULL          esperado: 1            obtenido: 1            OK
[ 5] contar_tokens(NULL)                esperado: 0            obtenido: 0            OK
[ 6] liberar_lista(NULL)                esperado: sin crash    obtenido: sin crash    OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
*¿Qué caso borde o problema omitió la IA y cómo lo solucionaste?*
La IA omitió comprobar algunos casos especiales al trabajar con los punteros. Lo solucioné revisando las condiciones necesarias antes de acceder o modificar los datos, para evitar errores durante la ejecución.
---
**Firma digital:** Emiliano Xooc Hau Ignacio Zaragoza
