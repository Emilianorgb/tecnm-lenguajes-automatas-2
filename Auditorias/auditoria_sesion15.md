# Bitácora de Requerimientos y Auditoría IA — Sesión 15
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Bloques Anidados y Ciclo de Vida  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Operaciones Push y Pop de ámbito  
Al realizar esta actividad, una de las dificultades fue comprender cómo se crean y se eliminan los ámbitos dentro de un programa. Para resolverlo utilicé dos operaciones: push_ambito() y pop_ambito().

La función push_ambito() permite crear un nuevo ámbito y enlazarlo con el anterior mediante el apuntador padre. Por otro lado, pop_ambito() permite cerrar el ámbito actual, liberar la memoria que ocupa y regresar al ámbito anterior.

También fue importante comprobar que no se libere el ámbito raíz, ya que este puede estar reservado fuera de las funciones.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Liberación de memoria al cerrar bloque |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar dos funciones para administrar ámbitos
anidados en lenguaje C.

La implementación debe:
- Crear nuevos ámbitos utilizando push_ambito().
- Enlazar cada ámbito con su padre.
- Cerrar el ámbito actual mediante pop_ambito().
- Liberar la memoria del ámbito que se cierra.
- Regresar el apuntador al ámbito padre.
- Evitar liberar el ámbito raíz.
- Validar los parámetros NULL.
- Controlar errores de reserva de memoria.
- Respetar la API proporcionada.
- No incluir una función main().
- Compilar con GCC usando -Wall -Wextra -Werror.

Entrega código modular y explica brevemente su funcionamiento.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA propuso una implementación basada en memoria dinámica, utilizando malloc() para crear nuevos ámbitos y free() para liberar los que se cierran.

Las funciones principales son:

Ambito *push_ambito(Ambito *actual, const char *nombre);

Ambito *pop_ambito(Ambito *actual);

La primera crea un nuevo ámbito y lo conecta con el anterior. La segunda obtiene el padre, libera el ámbito actual y devuelve el apuntador al ámbito anterior.

El código completo se encuentra en el archivo ia_sesion15_c.c.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Aislamiento de variables fuera de bloque

### Salida del harness
```text
Pega aquí la salida de la celda del harness. Debe terminar con:
=== AUDITORIA SESION 15 - Push y pop de ambitos ===
Caso                               esperado:              obtenido:              resultado
[ 1] nombre del ambito nuevo            esperado: if           obtenido: if           OK
[ 2] profundidad con dos push           esperado: 3            obtenido: 3            OK
[ 3] pop devuelve el padre              esperado: 1            obtenido: 1            OK
[ 4] pop sobre la raiz                  esperado: 1            obtenido: 1            OK
[ 5] push con padre NULL                esperado: 1            obtenido: 1            OK
[ 6] profundidad tras pop               esperado: 2            obtenido: 2            OK

RESULTADO: 6/6 pruebas superadas```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Un punto importante de esta actividad fue evitar que se libere el ámbito raíz, porque no necesariamente fue creado con malloc() dentro de push_ambito().

También fue necesario conservar el apuntador al padre antes de liberar el ámbito actual. De esta manera, pop_ambito() puede regresar correctamente al bloque anterior sin perder la referencia.

Otro aspecto importante es comprobar que la reserva de memoria haya funcionado antes de utilizar el nuevo ámbito.
> 

---
**Firma digital:** Emiliano Xooc Hau
