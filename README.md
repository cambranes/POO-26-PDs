# POO-26-PDs

Repositorio oficial para actividades individuales de la asignatura **Programación Orientada a Objetos**.

Este curso está dirigido a estudiantes de **tercer semestre de Ingeniería en Software**, con antecedentes en algoritmia, lógica computacional básica y programación estructurada.

## Pruebas de Desempeño
| *PD1*  | ..
|---|---|
| Título | PD-1 |
| Fecha de Entrega | Primer viernes de Septiembre |
| Instrucciones | [Ver descripción completa en PD1](PD1.md) |




## Documentación de la solución

### Descripción del diseño

La solución implementa una lista simplemente ligada para almacenar y administrar los stands. Cada nodo contiene la información correspondiente a un stand y un puntero hacia el siguiente nodo de la lista. Para la creación de los nodos se utiliza memoria dinámica mediante `malloc()`, y para liberar la memoria utilizada se emplea `free()`, las operaciones principales permiten crear, insertar, buscar, actualizar, eliminar e imprimir los stands. La lista se mantiene ordenada de acuerdo con el área de cada stand, utilizando el cálculo de ancho por largo para determinar su posición dentro de la lista.

### Decisiones importantes

Una decisión importante fue mantener la lista ordenada por área desde el momento en que se inserta cada stand. De esta manera, no es necesario ordenar nuevamente toda la lista después de cada inserción. La función `insertarOrdenadoPorArea()` determina la posición correspondiente y ajusta los punteros para insertar el nuevo nodo correctamente, incluyendo el caso en el que el nodo debe quedar al inicio de la lista.

También se utilizó memoria dinámica para permitir que la cantidad de stands pueda crecer según sea necesario. Al eliminar un stand o finalizar el programa, se libera la memoria correspondiente para evitar fugas de memoria.

### Retos y soluciones

Uno de los principales retos fue trabajar con punteros y memoria dinámica en una lista simplemente ligada, especialmente al insertar o eliminar nodos sin perder las referencias de la lista. Para resolverlo, se revisó el funcionamiento de los punteros y se controlaron los casos especiales, como insertar o eliminar el primer nodo otro reto fue asegurar que las funciones fueran compatibles con los prototipos definidos en `stand.h`. Se verificó la compilación del proyecto y se realizaron pruebas de ejecución utilizando `make` y `make run` para comprobar que la implementación funcionara correctamente.
