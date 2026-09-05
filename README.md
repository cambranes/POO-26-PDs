# POO-26-PDs

Repositorio oficial para actividades individuales de la asignatura **Programación Orientada a Objetos**.

## Descripción del Diseño

El diseño de este código se fundamenta en una lista simplemente ligada en C, construida con un enfoque modular y encapsulado. La estructura principal `(Stand)` representa individualmente cada espacio de la exhibición, almacenando un id numérico, las dimensiones `(ancho y largo)`, un tipo enumerado `(StandEstado)` para controlar el estado del stand `(disponible, reservado, vendido)` y un puntero de enlace hacia el siguiente elemento de la lista.

Para tener control sobre la estructura de datos, todas las operaciones que modifican la estructura de la lista reciben un puntero doble `(Stand **cabeza)`. Esto permite alterar directamente el puntero de inicio de la lista desde cualquier función sin necesidad de recurrir a variables globales. Además, el diseño sigue un enfoque de manipulación por referencia en donde cada nodo se gestiona de manera individual en memoria dinámica (heap), lo que facilita la inserción y eliminación de registros sin los límites de un arreglo estático.

## Decisiones Importantes del Código

* **Criterio y Mantenimiento Dinámico del Orden:** La lista debe de permanecer oordenada de menor a mayor área según el cálculo de `ancho * largo`. Para no perder este orden al modificar un registro existente, la función `actualizarStand` detecta si las nuevas dimensiones alteran el área del stand y, de ser así, desvincula temporalmente el nodo de su posición y llama a `insertarOrdenadoPorArea` para reubicarlo automáticamente en su lugar correspondiente.
* **Control de Casos Límite y Retornos de Estado:** Para prevenir accesos indebidos a memoria y comportamientos indefinidos, las funciones de modificación y búsqueda integran verificaciones strictly para listas vacías (`*cabeza == NULL`) o punteros nulos. Además, las funciones de borrado y actualización devuelven valores booleanos (`1` para éxito y `0` para fallo) para notificar al módulo llamante si el ID buscado no existía.
* **Prevención de Fugas de Memoria (*Memory Leaks*):** En la función `liberarLista`, la eliminación de los nodos asignados dinámicamente con `malloc` utiliza un puntero temporal auxiliar (`sig`) para guardar la dirección del siguiente nodo antes de aplicar `free` sobre el nodo actual. Esto evita la pérdida de referencias en memoria durante el recorrido de eliminación y asegura que al finalizar la ejecución la variable `cabeza` quede apuntando a `NULL`.

## Retos enfrentados

Uno de los retos que enfrente en el proceso fué que mi código marcaba errores y no lograba dar con el por qué, pues eran línead básicas que no tenían que marcar error. Para resolverlo tuve que instalar un programa que resolvió mi problema en ese momento, aunque después me topé con algo similar, solo que está vez el código no compilaba cuando ingresaba make run en la terminal. Resultó que tenía que ingresar un comando diferente para que lograra compilar.

**Enlace al vídeo técnico:** https://youtu.be/lNsWaCnhkz8 