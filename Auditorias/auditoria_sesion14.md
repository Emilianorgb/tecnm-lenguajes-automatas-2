**# Bitácora de Requerimientos y Auditoría IA — Sesión 14
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Declaración vs Uso de Variables  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Detección de variables no declaradas  
Al realizar esta actividad, una de las dificultades fue controlar que una variable estuviera declarada antes de utilizarla. Para resolverlo, fue necesario crear una estructura que almacena los nombres de las variables registradas.

También tuve que considerar qué sucede cuando se intenta declarar dos veces el mismo nombre. En ese caso, el programa debe detectar la redeclaración y evitar que se agregue nuevamente a la tabla.

Para realizar las comparaciones utilicé la función strcmp(), que permite comprobar si dos nombres son exactamente iguales.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Invariante de definición previa |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar un sistema para controlar la declaración
y el uso de variables en lenguaje C.

La implementación debe:
- Permitir declarar nombres de variables.
- Evitar que un nombre se declare dos veces.
- Comprobar si una variable ya fue declarada antes de utilizarla.
- Diferenciar nombres completos, por ejemplo x y xy.
- Controlar parámetros NULL y nombres vacíos.
- Respetar la API proporcionada.
- No incluir una función main().
- Compilar con GCC usando -Wall -Wextra -Werror.

Entrega código modular y explica brevemente su funcionamiento.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA propuso una solución basada en una tabla que almacena los nombres de las variables declaradas.

Las funciones principales son:

int declarar(Tabla *tabla, const char *nombre);

int usar(const Tabla *tabla, const char *nombre);

La función declarar() registra una variable si todavía no existe. Si el nombre ya está registrado, evita que se agregue nuevamente.

La función usar() revisa si el identificador se encuentra dentro de la tabla. Si existe devuelve 1; si no existe devuelve 0.

El código completo se encuentra en el archivo ia_sesion14_c.c.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Uso antes de declarar y redeclaración

### Salida del harness
```text
Pruebas ejecutadas: 6 casos relacionados con el uso antes de declarar y la redeclaración de variables.

Casos revisados

Prueba

Descripción

1

Intentar utilizar una variable sin declararla.

2

Utilizar una variable después de declararla.

3

Intentar declarar dos veces el mismo nombre.

4

Comprobar que el total no aumente al redeclarar.

5

Comprobar que x y xy sean identificadores diferentes.

6

Intentar declarar un nombre vacío.

Salida del harness

=== AUDITORIA SESION 14 - Declaracion previa y redeclaracion ===
Caso                               esperado:              obtenido:              resultado
[ 1] usar sin declarar                  esperado: 0            obtenido: 0            OK
[ 2] usar despues de declarar           esperado: 1            obtenido: 1            OK
[ 3] redeclarar el mismo nombre         esperado: 0            obtenido: 0            OK
[ 4] total tras redeclarar              esperado: 1            obtenido: 1            OK
[ 5] prefijo no es el mismo nombre      esperado: 0            obtenido: 0            OK
[ 6] declarar nombre vacio              esperado: -1           obtenido: -1           OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Uno de los casos importantes de esta actividad es diferenciar los nombres que solamente comparten algunas letras. Por ejemplo, x y xy deben considerarse variables diferentes.

Para evitar errores en las comparaciones se utilizó strcmp(), que revisa el contenido completo de los nombres.

También se consideró que una variable no puede utilizarse antes de haber sido declarada y que una redeclaración dentro de la misma tabla debe ser rechazada.
> 

---
**Firma digital:** Emiliano Xooc Hau
