# Bitácora de Requerimientos y Auditoría IA — Sesión 03
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Google Colab, Mágicos y Flujo de Entrega  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Manipulación de archivos y llamadas OS  
En esta actividad trabajé con archivos desde el lenguaje C. La idea era crear un archivo de texto, escribir información y después leerlo para saber cuántas líneas contiene.

Una de las partes que más atención necesitó fue contar correctamente las líneas. Me di cuenta de que no basta con contar los saltos de línea, porque también puede existir una última línea que no termine con \n.

Además, tuve que revisar que el archivo se abriera correctamente y cerrarlo después de utilizarlo. Si la ruta no existe o no se puede abrir el archivo, la función debe informar el error en lugar de continuar como si todo hubiera salido bien.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Salida estándar y códigos de retorno ABI |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Necesito resolver una práctica de C relacionada con el manejo
de archivos de texto.

Quiero que desarrolles dos funciones: una para guardar texto
en un archivo y otra para leerlo y contar cuántas líneas contiene.

Las funciones deben llamarse escribir_texto y contar_lineas,
y conservar exactamente las firmas del archivo api_sesion03.h.

Hay algunos detalles que no quiero que se pasen por alto:

- Si el archivo no se puede abrir, la función debe devolver -1.
- Si ocurre un error al escribir o leer, también debe reportarlo.
- Una línea debe contarse aunque no termine con un salto de línea.
- Un archivo vacío debe devolver cero.
- Los archivos deben cerrarse correctamente.
- No agregues una función main porque el programa de pruebas
  ya cuenta con una.

Utiliza funciones estándar de C como fopen, fputs, fgetc
y fclose. Quiero una solución clara, compatible con C99
y que pueda compilarse con GCC usando -Wall -Wextra -Werror.

Al terminar, explica brevemente cómo se realiza el conteo
de líneas y cómo se manejan los errores.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA presentó una solución dividida en dos funciones.

La primera, escribir_texto(), se encarga de abrir el archivo en modo escritura y guardar el contenido recibido. Antes de hacerlo comprueba que los datos sean válidos y que el archivo se pueda abrir.

La segunda, contar_lineas(), lee el archivo carácter por carácter. Cada vez que encuentra un salto de línea aumenta el contador. También revisa el último carácter leído para incluir una línea que no tenga salto de línea al final.

Al terminar, ambas funciones comprueban los errores que pueden presentarse y cierran el archivo.

Funciones principales:

escribir_texto()

contar_lineas()
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Detección de errores de compilación GCC

### Salida del harness
```text
=== AUDITORIA SESION 03 - Archivos: escribir y contar lineas ===
Caso                               esperado:              obtenido:              resultado
[ 1] escribir_texto(...)==0             esperado: 0            obtenido: 0            OK
[ 2] contar_lineas(3 lineas)            esperado: 3            obtenido: 3            OK
[ 3] contar_lineas(sin salto final)     esperado: 2            obtenido: 2            OK
[ 4] contar_lineas(archivo vacio)       esperado: 0            obtenido: 0            OK
[ 5] contar_lineas(inexistente)         esperado: -1           obtenido: -1           OK
[ 6] escribir_texto(ruta invalida)      esperado: -1           obtenido: -1           OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
*¿Qué caso borde o problema omitió la IA y cómo lo solucionaste?*
La IA podía omitir el manejo de errores al trabajar con archivos, por ejemplo, cuando no se podía abrir un archivo o la ruta no existía. Lo solucioné comprobando si el archivo se abría correctamente y devolviendo -1 cuando ocurría un error.

---
**Firma digital:** Emiliano Xooc Hau Ignacio Zaragoza
