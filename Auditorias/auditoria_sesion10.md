# Bitácora de Requerimientos y Auditoría IA — Sesión 10
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Hito 1: Mini-Evaluador de Expresiones  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Integración AST y Tipado Estático  
Al realizar el evaluador manualmente, una de las principales dificultades fue organizar las operaciones para que se respetara la prioridad matemática. Por ejemplo, primero se deben resolver las multiplicaciones y divisiones antes que las sumas y restas.

También fue necesario trabajar con funciones recursivas para reconocer los paréntesis y evaluar las expresiones correctamente.

Durante la compilación encontré un problema porque faltaba incluir la biblioteca ctype.h, necesaria para utilizar las funciones isspace() e isdigit(). Al agregarla se corrigió ese error.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Contrato formal de Frontend Semántico |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Actúa como un ingeniero de software especializado en compiladores.

Necesito implementar en lenguaje C una función llamada
evaluar_expresion para evaluar expresiones aritméticas.

Debe aceptar:
- Sumas y restas.
- Multiplicaciones y divisiones.
- Números negativos.
- Paréntesis.
- Espacios en blanco.

Debe respetar la prioridad de las operaciones.

El código debe detectar:
- División entre cero, utilizando el error 1.
- Sintaxis incorrecta, utilizando el error 2.

Utiliza análisis recursivo y funciones auxiliares.
No utilices eval ni bibliotecas externas.
No incluyas una función main().
Respeta la API proporcionada y permite compilar con GCC
utilizando -Wall -Wextra -Werror.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA propuso una solución basada en análisis recursivo. El programa utiliza funciones auxiliares para separar los factores, términos y expresiones.

La implementación se encuentra en el archivo ia_sesion10_c.c.

La función principal es:

long evaluar_expresion(const char *fuente, int *error);

Esta función recibe la expresión, realiza su evaluación y devuelve el resultado. Si encuentra un problema, establece el código de error correspondiente.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Batería de 10 expresiones mixtas complejas

### Salida del harness
```text
Pruebas ejecutadas: 6 expresiones proporcionadas por el laboratorio.

Salida del harness

Se realizaron las siguientes pruebas:

Prueba

Expresión

Resultado esperado

1

2+3*4

14

2

(2+3)*4

20

3

10/0

Error 1

4

2+

Error 2

5

 7

7

6

-5+10

5

Problemas encontrados durante la compilación:

En Artesano apareció un error por no incluir ctype.h, que contiene las funciones isspace() e isdigit().

En Científico apareció otro error porque se utilizó NULL sin incluir stddef.h.

Se corrigieron ambos problemas agregando las bibliotecas correspondientes.

=== AUDITORIA SESION 10 - Mini-evaluador de expresiones (Hito 1) ===
Caso                               esperado:              obtenido:              resultado
[ 1] "2+3*4"                            esperado: 14           obtenido: 14           OK
[ 2] "(2+3)*4"                          esperado: 20           obtenido: 20           OK
[ 3] "10/0" -> error 1                  esperado: 1            obtenido: 1            OK
[ 4] "2+" -> error 2                    esperado: 2            obtenido: 2            OK
[ 5] "  7 "                             esperado: 7            obtenido: 7            OK
[ 6] "-5+10"                            esperado: 5            obtenido: 5            OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
El principal problema detectado en las primeras compilaciones fue la falta de algunas bibliotecas necesarias. En Artesano faltaba ctype.h y en Científico faltaba stddef.h.

Estos errores se identificaron al ejecutar el compilador con las opciones -Wall -Wextra -Werror, que permiten detectar advertencias y tratarlas como errores.

La solución fue agregar las bibliotecas correspondientes sin modificar la lógica principal del evaluador.
> 

---
**Firma digital:** Emiliano Xooc Hau
