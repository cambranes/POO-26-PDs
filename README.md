# POO-26-PDs
## Documentación de la Solución (PD1)

### Descripción del Diseño
La solución implementa un sistema CRUD para la gestión de stands de exposición mediante una lista simplemente ligada en C. Cada nodo contiene la información relevante del stand (número, dimensiones y estado) y un puntero al siguiente elemento de la lista. El diseño permite manipular los datos de forma modular evitando variables globales y garantizando el manejo dinámico de memoria.

Las operaciones están estructuradas para garantizar un flujo claro: la creación e inserción ubican los nodos de forma ordenada según su área, las búsquedas se realizan de forma secuencial por el número identificador, y las modificaciones o liberaciones de memoria ajustan los punteros correctamente para evitar fuga de recursos.

### Retos Enfrentados y Soluciones
- **Ajustes finales post-grabación**: El video explicativo se grabó en una etapa previa donde la prueba de escritorio incluía la función main dentro de stand.c. Para cumplir con la estructura requerida del proyecto, la función main se movió al archivo main.c y se ajustaron los nombres de las variables y tipos de datos para alinearse estrictamente a stand.h. Aunque el video muestra una versión anterior con ligeras variaciones de estructura, la sintaxis, la lógica del algoritmo de lista ligada y el comportamiento de las funciones son exactamente los mismos que se subieron al repositorio.
