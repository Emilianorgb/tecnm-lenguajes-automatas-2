# Bitácora de Requerimientos y Auditoría IA — Sesión 13
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Manejo de Ámbitos (Scope Global/Local)  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Pila de tablas de símbolos (Stack Scopes)  
Al realizar esta actividad, una de las dificultades fue comprender cómo funciona la búsqueda de variables dentro de diferentes ámbitos. Por ejemplo, una variable puede estar declarada en el ámbito global y también en un bloque local.

Para resolverlo utilicé una estructura enlazada mediante el campo padre, que permite recorrer los ámbitos desde el más cercano hasta el más externo.

También tuve que considerar el ocultamiento de variables (shadowing), porque cuando dos ámbitos tienen una variable con el mismo nombre, debe tener prioridad la declaración que se encuentra en el ámbito más cercano.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Ocultamiento de variables (Shadowing) |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar un sistema de ámbitos globales y locales
en lenguaje C.

La implementación debe:
- Permitir declarar identificadores en un ámbito.
- Evitar declaraciones duplicadas en el mismo ámbito.
- Permitir el mismo nombre en ámbitos diferentes.
- Implementar el ocultamiento de variables (shadowing).
- Buscar identificadores desde el ámbito actual hacia sus padres.
- Devolver el nombre del ámbito donde se encontró el identificador.
- Controlar los parámetros NULL.
- Respetar la API proporcionada.
- No incluir una función main().
- Compilar con GCC usando -Wall -Wextra -Werror.

Entrega código modular y explica brevemente su funcionamiento.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA propuso una implementación utilizando una estructura de ámbitos enlazados mediante un apuntador llamado padre.

Las funciones principales son:

int declarar(Ambito *ambito, const char *nombre);

const char *buscar(
    const Ambito *ambito,
    const char *nombre
);

La función declarar() permite registrar identificadores en el ámbito actual y evita que se repitan dentro del mismo bloque.

La función buscar() recorre los ámbitos desde el más cercano hasta el global, permitiendo encontrar la declaración correspondiente.

El código completo se encuentra en el archivo ia_sesion13_c.c.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Búsqueda jerárquica de identificadores

### Salida del harness
```text
Pruebas ejecutadas: 6 casos relacionados con la declaración y búsqueda jerárquica de identificadores.

Casos revisados

Prueba

Descripción

1

Declarar una variable en un ámbito.

2

Buscar una variable en el mismo ámbito.

3

Buscar una variable declarada en el ámbito padre.

4

Comprobar el ocultamiento de una variable (shadowing).

5

Buscar una variable en tres niveles de ámbitos.

6

Comprobar que un identificador inexistente devuelva NULL.

Salida del harness
=== AUDITORIA SESION 13 - Pila de ambitos y busqueda jerarquica ===
Caso                               esperado:              obtenido:              resultado
[ 1] declarar(&g, "x")                  esperado: 1            obtenido: 1            OK
[ 2] buscar en el mismo ambito          esperado: global       obtenido: global       OK
[ 3] buscar subiendo al padre           esperado: global       obtenido: global       OK
[ 4] shadowing en el hijo               esperado: bloque       obtenido: bloque       OK
[ 5] tres niveles hasta la raiz         esperado: raiz         obtenido: raiz         OK
[ 6] nombre no declarado                esperado: (nulo)       obtenido: (nulo)       OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Un punto importante de esta actividad fue comprobar que una variable declarada en un ámbito local pueda tener el mismo nombre que otra variable global.

Al buscar ese identificador desde el ámbito local, debe encontrarse primero la declaración más cercana. Para conseguirlo, la búsqueda recorre la estructura desde el ámbito actual hacia los ámbitos superiores.

También se debe revisar que no se permitan nombres duplicados dentro del mismo ámbito y que una búsqueda de un identificador inexistente devuelva NULL.
> 

---
**Firma digital:** Emiliano Xooc Hau
