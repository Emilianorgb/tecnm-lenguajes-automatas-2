# Bitácora de Requerimientos y Auditoría IA — Sesión 07
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Evaluación de Expresiones Aritméticas  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau.  
**Matrícula:** 24531402.
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
En esta parte trabajé en un evaluador de operaciones matemáticas utilizando árboles sintácticos. La idea era que el programa pudiera resolver operaciones como sumas, restas, multiplicaciones y divisiones.

Al principio tuve algunas dificultades para organizar las llamadas recursivas y comprobar que los nodos del árbol fueran válidos. También tenía que considerar qué hacer cuando se intentaba dividir entre cero.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Manejo estricto de división entre cero |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Necesito que desarrolles un evaluador de expresiones
aritméticas en lenguaje C utilizando árboles sintácticos.

Respeta las funciones declaradas en api_sesion07.h.
El programa debe evaluar sumas, restas, multiplicaciones,
divisiones y módulos.

También debe detectar la división entre cero, el módulo
entre cero y los nodos NULL.

No agregues una función main y utiliza código modular
que pueda compilarse con GCC.
```

---

## 3. Código Devuelto por el Modelo
```c
En esta sección se incluye el código que generó la inteligencia artificial para el archivo ia_sesion07_c.c.

La propuesta utiliza una función auxiliar para recorrer los nodos y realizar las operaciones. También comprueba los errores antes de continuar con la evaluación.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Expresiones complejas y división por 0

### Salida del harness
```text
Durante las pruebas aparecieron algunos problemas de compilación.

En el archivo del Científico apareció un error porque se utilizaba NULL sin incluir la biblioteca correspondiente. Se solucionó agregando #include <stddef.h>.

En el Artesano también apareció el mismo problema. Para corregirlo se agregó el encabezado necesario.

Después de corregir el Científico, ejecuté nuevamente el auditor y obtuve los siguientes resultados:
=== AUDITORIA SESION 07 - Evaluador recursivo con deteccion de errores ===

[1] (2+3)*4          esperado: 20    obtenido: 20    OK
[2] 7/0              esperado: 1     obtenido: 1     OK
[3] 7%0              esperado: 1     obtenido: 1     OK
[4] arbol NULL       esperado: 2     obtenido: 2     OK
[5] 10-2-3           esperado: 5     obtenido: 5     OK
[6] (8/2)+1          esperado: 5     obtenido: 5     OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Uno de los problemas que encontré fue que el código utilizaba NULL, pero no tenía incluido el encabezado stddef.h. Por ese motivo, el compilador no reconocía esa palabra y no permitía ejecutar el programa.

Lo solucioné agregando #include <stddef.h> en el archivo correspondiente. También comprobé que el programa pudiera detectar una división entre cero, un módulo entre cero y un árbol vacío.

Después de hacer las correcciones, el Científico pasó las seis pruebas del auditor.


> 

---
**Firma digital:** Emiliano Xooc Hau
