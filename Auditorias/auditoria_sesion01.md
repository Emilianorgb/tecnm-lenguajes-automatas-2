# Bitácora de Requerimientos y Auditoría IA — Sesión 01
**Materia:** Lenguajes y Autómatas II (SCD-1016)  
**Tema:** Encuadre, Diagnóstico de Punteros y Metodología IA  
**Docente Titular:** MCC. Iván Márquez Larios (`ijmarquezl`)  
**Estudiante:** Emiliano Xooc Hau  
**Matrícula:** 24531402  
**Track:** C (el harness evalúa C; la versión en Rust es opcional y no se califica con este harness)  

---

## 1. Fase 1: El Artesano (Dificultad Manual)
*Reto:* Inversión de buffer in-place (char*)  
En esta primera actividad trabajé con una función que permite invertir una cadena de texto sin utilizar otro arreglo para guardar los caracteres.

Al principio puede parecer sencillo, pero la parte que requiere más atención es el uso de los punteros, porque hay que recorrer la cadena desde ambos extremos y cambiar los caracteres de lugar.

También fue importante tener cuidado con las cadenas vacías y con los apuntadores que no contienen una dirección válida, para evitar errores al ejecutar el programa.
> 

---

## 2. Fase 2: El Científico (Ingeniería de Requerimientos C-R-E-O)

### 2.1 Matriz de Especificación Formal
| Elemento C-R-E-O | Definición Técnica |
| :--- | :--- |
| **Contexto (C)** | C99 / GCC o Rust 2021 sin bibliotecas no estándar |
| **Rol (R)** | Ingeniero de software de sistemas y compiladores |
| **Especificación (E)** | Punteros, O(n) tiempo, O(1) memoria |
| **Output (O)** | Solo código modular y análisis de complejidad |

### 2.2 Prompt Estructurado
```text
Quiero que me ayudes a resolver un ejercicio en lenguaje C.

Tengo que crear una función que invierta una cadena de texto,
pero hay una condición: no quiero utilizar otro arreglo para
guardar el resultado. Quiero que los cambios se hagan directamente
en la cadena original.

Me gustaría que la solución utilice dos punteros:
uno al inicio y otro al final de la cadena, para ir cambiando
los caracteres hasta llegar al centro.

También necesito que tomes en cuenta lo siguiente:
- Que no falle si recibe NULL.
- Que pueda trabajar con una cadena vacía.
- Que funcione con cadenas pares e impares.
- Que no utilice memoria adicional.
- Que sea compatible con GCC y C99.

Dame la función sin incluir main() y explícame
de manera sencilla cómo funciona.
```

---

## 3. Código Devuelto por el Modelo
```c
La IA propuso utilizar dos punteros para realizar el intercambio de caracteres. Uno comienza en la primera posición de la cadena y el otro se coloca al final.

Después, ambos avanzan hacia el centro mientras intercambian los caracteres que encuentran. El proceso termina cuando los punteros se encuentran o se cruzan.

Lo interesante de esta solución es que no necesita crear otra cadena, porque modifica directamente la original.
```

---

## 4. Fase 3: El Auditor (Resultados del Test Harness)
*Pruebas ejecutadas:* Valores NULL, buffers vacios y longitudes impares

### Salida del harness
```text
=== AUDITORIA SESION 01 - Inversion de buffer in-place ===
Caso                               esperado:              obtenido:              resultado
[ 1] invertir("HOLA")                   esperado: ALOH         obtenido: ALOH         OK
[ 2] invertir("abc")                    esperado: cba          obtenido: cba          OK
[ 3] invertir("")                       esperado:              obtenido:              OK
[ 4] invertir("AB")                     esperado: BA           obtenido: BA           OK
[ 5] invertir("a")                      esperado: a            obtenido: a            OK
[ 6] invertir(NULL)                     esperado: sin crash    obtenido: sin crash    OK

RESULTADO: 6/6 pruebas superadas
```

* [ ] Caso base y límites superados sin *Crash*.
* [ ] No existen accesos fuera de límites ni *Memory Leaks*.
* [ ] La complejidad teórica coincide con la implementada.

### Reporte Crítico
*¿Qué caso borde o problema omitió la IA y cómo lo solucionaste?*
La IA omitió el caso borde de evaluar un árbol nulo (NULL). Al principio, la función no contemplaba qué hacer cuando no recibía un nodo válido. Lo solucioné agregando una condición al inicio de evaluar para que, si el nodo es NULL, devuelva -1 y el programa no intente acceder a una dirección de memoria inválida. Después ejecuté las pruebas del auditor para comprobar que funcionara correctamente.

---
**Firma digital:** 
Emiliano Xooc Hau Ignacio Zaragoza
