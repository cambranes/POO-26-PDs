# POO-26-PDs

Repositorio oficial para actividades individuales de la asignatura **Programación Orientada a Objetos**.

Este curso está dirigido a estudiantes de **tercer semestre de Ingeniería en Software**, con antecedentes en algoritmia, lógica computacional básica y programación estructurada.

## Video :
https://youtu.be/qP31NjBo_dU

## PD1 - Stands (Listas Simplemente Ligadas)

### Descripcion del Proyecto

Esta tarea consiste en la implementacion de un sistema de gestion de stands para una feria de libros usando listas simplemente ligadas en C. El objetivo era trabajar con apuntadores, memoria dinamica y estruturas de datos ordenadas.

La solucion mantiene una lista de stands ordenada por area (ancho x largo en metros cuadrados). Cada stand tiene un numero identificador, dimensiones y un estado (Disponible, Reservado o Vendido).

### Diseño de la Solucion

**Estructura de datos:**
- Se utiliza una estructura `Stand` que contiene: numero, ancho, largo, estado y un apuntador al siguiente nodo
- La lista se ordena automaticamente por area cada vez que se inserta o actualiza un stand
- Se utiliza memoria dinamica con `malloc()` para cada nodo y se libera correctamente con `free()`

**Funciones principales:**
- `crearStand()`: Crea un nuevo stand en memoria
- `insertarOrdenadoPorArea()`: Inserta respetando el orden de area
- `buscarStand()`: Busca un stand por numero
- `actualizarStand()`: Modifica los datos y reinsertar si el area cambia
- `borrarStand()`: Elimina un stand y libera su memoria
- `imprimirLista()`: Muestra todos los stands en una tabla formateada

### Decisiones de Diseño

La principal decision fue hacer que la lista se reordene automaticamente cuando la area de un stand cambia. Esto significa que si actualizas un stand con una nueva area mas pequeña, se movera hacia el inicio de la lista. Se logro esto removiendo el stand, creando uno nuevo con los datos actualizados e insertandolo nuevamente en la posicion correcta.

### Retos Enfrentados

El principal reto fue readaptarse al lenguaje C despues de mucho tiempo sin usarlo. Particularmente, recordar como funcionan los apuntadores, la memoria dinamica y la manipulacion de listas ligadas. Tambien fue necesario tener cuidado con la liberacion de memoria para evitar memory leaks.

---

| *PD1*  | Stands - Listas Simplemente Ligadas |
|---|---|
| Fecha de Entrega | Primer viernes de Septiembre |
| Instrucciones | [Ver descripción completa en PD1](PD1.md) |
