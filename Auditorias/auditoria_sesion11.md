# Bitácora de Requerimientos y Auditoría IA — Sesión 11
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Arquitectura de la Tabla de Símbolos  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Tabla Hash con encadenamiento  
Al realizar la tabla hash manualmente, una de las dificultades fue comprender cómo distribuir los símbolos dentro de las cubetas. También tuve que trabajar con memoria dinámica para crear nuevos nodos y enlazarlos cuando dos nombres producían la misma posición.

Para resolver las colisiones utilicé el método de encadenamiento, que permite guardar varios símbolos en una misma cubeta mediante una lista enlazada.

Otro punto importante fue revisar que no se insertaran nombres duplicados y que la memoria se reservara correctamente con malloc().
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Función de dispersión y colisiones O(1) |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar una tabla de símbolos en lenguaje C.

Utiliza el algoritmo hash djb2 para calcular la posición
de cada nombre dentro de la tabla.

La implementación debe:
- Permitir insertar símbolos.
- Detectar nombres duplicados.
- Manejar colisiones mediante listas enlazadas.
- Guardar nombre, tipo y offset.
- Controlar errores de memoria.
- Validar los parámetros recibidos.
- Respetar la API proporcionada.
- No incluir una función main().
- Compilar con GCC usando -Wall -Wextra -Werror.

Entrega código modular y explica brevemente
la complejidad de las operaciones.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA propuso una implementación utilizando el algoritmo djb2 para calcular el índice de cada símbolo.

También organizó la inserción mediante funciones auxiliares para revisar si un nombre ya existe y evitar duplicados.

El código se encuentra en el archivo ia_sesion11_c.c.

Las funciones principales son:

unsigned int hash_djb2(const char *clave);

int insertar_simbolo(
    Simbolo *tabla[],
    unsigned int cubetas,
    const char *nombre,
    int tipo,
    int offset
);

La primera calcula el valor hash y la segunda inserta el símbolo en la tabla, utilizando encadenamiento cuando existen colisiones.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Manejo de claves duplicadas y colisiones

### Salida del harness
```text
Pruebas ejecutadas: 6 casos relacionados con el cálculo hash, duplicados, colisiones y validación de parámetros.

Casos revisados

Prueba

Descripción

1

Calcular el hash de una cadena vacía.

2

Calcular el hash de la cadena abc.

3

Intentar insertar dos veces el mismo símbolo.

4

Insertar dos símbolos en una sola cubeta.

5

Comprobar el offset de un símbolo dentro de una colisión.

6

Intentar insertar en una tabla NULL.

Salida del harness

=== AUDITORIA SESION 11 - Tabla hash con encadenamiento ===
Caso                               esperado:              obtenido:              resultado
[ 1] hash_djb2("")                      esperado: 5381         obtenido: 5381         OK
[ 2] hash_djb2("abc")                   esperado: 193485963    obtenido: 193485963    OK
[ 3] insertar x dos veces               esperado: 0            obtenido: 0            OK
[ 4] dos claves, una cubeta             esperado: 2            obtenido: 2            OK
[ 5] offset de beta en cadena           esperado: 4            obtenido: 4            OK
[ 6] insertar en tabla NULL             esperado: -1           obtenido: -1           OK

RESULTADO: 6/6 pruebas superadas```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Durante la revisión de la implementación es importante comprobar que los nombres duplicados se detecten en toda la tabla y no solamente en la cubeta calculada para el nuevo nombre.

También se debe verificar que las colisiones no provoquen la pérdida de información y que cada nodo conserve su nombre, tipo y offset.

La reserva de memoria con malloc() debe comprobarse antes de utilizar el nuevo nodo, para evitar errores cuando no hay memoria disponible.
> 

---
**Firma digital:** Emiliano Xooc Hau
