# Descripción de diseño
## Propuesta
Para mi propuesta al problema solicitado, he elaborado un programa que administra los stands usando una
lista simplemente ligada, cada stand es un nodo independiente que por medio de punteros se conecta a otros stands, se decidio usar este enfoque debido a que permite que la cantidad de stands pueda crecer o disminuir sin tener que definir un limite maximo de memoria. La lista se encuentra ordenada de manera ascendente (menor a mayor), el criterio de ordenacion usado fue el area total de los stands (largo x ancho)

## Decisiones y retos
Hablando de decisiones importantes.
Tuvo que ver con cómo manejar la reordenación cuando un stand cambia de tamaño. En vez de borrar el stand y crear uno nuevo con los datos actualizados, el programa lo desconecta temporalmente de su posición actual (sin liberar la memoria que ocupa) y lo vuelve a insertar en el lugar que le corresponde según su nueva área.
un reto que tuve a la hora de elaborar este programa fue adaptar el código y su funcionalidad a los prototipos ya existentes, mi visión para la solucion era bastante diferente al código que entregue
