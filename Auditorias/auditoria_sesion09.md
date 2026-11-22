# Bitácora de Requerimientos y Auditoría IA — Sesión 09
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Reporte Formal de Errores Semánticos  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Diagnóstico con línea y columna  
En esta actividad trabajé en una función llamada reportar(), que sirve para mostrar mensajes de error indicando el nombre del archivo, la línea y la columna donde se encuentra el problema.

Al principio tuve que revisar cómo juntar todos esos datos en una sola cadena de texto. También debía tener cuidado con el tamaño del buffer, porque no podía escribir más caracteres de los que tenía disponibles.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Estructura estándar de errores GCC |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Necesito que desarrolles una función llamada reportar()
en lenguaje C.

Debe recibir el nombre del archivo, número de línea,
columna, mensaje, buffer de salida y capacidad del buffer.

El resultado debe tener este formato:
archivo:linea:columna: error: mensaje

Respeta exactamente la firma declarada en
api_sesion09.h.

Utiliza snprintf para evitar desbordamientos del buffer.
No agregues una función main y utiliza código compatible
con GCC.
```

---

## 3. Código Devuelto por el Modelo
```c
La inteligencia artificial propuso utilizar la función snprintf() para construir el mensaje de error.

Después coloqué el código en ia_sesion09_c.c y revisé que respetara la función declarada en el archivo de encabezado.

También comprobé que no tuviera una función main(), porque esa parte corresponde al auditor.

```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Múltiples errores sin abortar parser

### Salida del harness
```text
Para comprobar el funcionamiento ejecuté el programa con cuatro casos diferentes.

Se revisó que los mensajes tuvieran el formato correcto y que el programa respetara el espacio disponible en el buffer.

Los casos fueron:

Un mensaje completo con archivo, línea y columna.

Un mensaje corto.

Una ubicación con línea y columna en cero.

Un mensaje que no cabe completo en un buffer de 10 caracteres.
=== AUDITORIA SESION 09 - Diagnostico con linea y columna ===

[ 1] main.c:14:5
     esperado: main.c:14:5: error: tipo incompatible
     obtenido: main.c:14:5: error: tipo incompatible
     -> OK

[ 2] a.c:1:1
     esperado: a.c:1:1: error: x
     obtenido: a.c:1:1: error: x
     -> OK

[ 3] linea 0
     esperado: x.c:0:0: error: y
     obtenido: x.c:0:0: error: y
     -> OK

[ 4] cap=10 trunca esperado: main.c:14 obtenido: main.c:14 OK

RESULTADO: 4/4 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
Uno de los puntos más importantes de esta práctica fue controlar el tamaño del buffer. Si el mensaje es más largo que el espacio disponible, no se deben escribir caracteres fuera de sus límites.

Para manejar esta situación se utilizó snprintf(), indicando la capacidad máxima del buffer. De esta manera, cuando el mensaje no cabe completo, se guarda solamente la parte que alcanza y se mantiene el carácter de terminación \0.

También se comprobó que el resultado pudiera generarse correctamente con diferentes nombres de archivos y posiciones.
> 

---
**Firma digital:** Emiliano Xooc Hau
