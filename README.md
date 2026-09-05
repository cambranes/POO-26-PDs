# POO-26-PDs

Repositorio oficial para actividades individuales de la asignatura **Programación Orientada a Objetos**.

Este curso está dirigido a estudiantes de **tercer semestre de Ingeniería en Software**, con antecedentes en algoritmia, lógica computacional básica y programación estructurada.

## Pruebas de Desempeño
| *PD1*  | ..
|---|---|
| Título | PD-1 |
| Fecha de Entrega | Primer viernes de Septiembre |
| Instrucciones | [Ver descripción completa en PD1](PD1.md) |
## Naomy Alférez

Para esta práctica, desarrollé un programa diseñado para organizar los stands de una feria de libros, 
funciona a través de una lista enlazada donde cada stand se va conectando con el siguiente, como si estuvieran formados en una fila. Cada uno de estos espacios guarda su propia información: su número de identificación, cuánto mide de ancho y de largo, y si está disponible o ya se vendió.

La regla más importante que le puse a este sistema es que la fila nunca puede estar desordenada. Siempre, sin excepción, los stands se van acomodando del más pequeño al más grande dependiendo de su área total. Cada vez que se registra un stand nuevo, el programa le hace un espacio a medida en la memoria de la computadora y lo forma exactamente en el lugar que le corresponde.

Una de las partes a las que más le dediqué tiempo fue a la actualización de los datos. Pensé: ¿qué pasa si un stand cambia sus medidas y de pronto se vuelve más grande que los que tiene a los lados? Para evitar que la fila se vuelva un desorden, el código hace algo muy práctico: saca momentáneamente el stand, recalcula su tamaño y lo vuelve a formar en su nueva posición correcta.

Ya por último me enfoqué mucho en la limpieza. Me aseguré de que al borrar un registro o cerrar por completo el programa, el sistema recoja todo y devuelva la memoria que usó, para queel programa termine de ejecutarse sin dejar basura en la computadora.
