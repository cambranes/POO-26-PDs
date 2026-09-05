#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

/* funcion que calcula el area de un stand */
float calcularArea(const Stand *stand) {
    if (stand == NULL) {
        return 0.0f; // en caso de que no exista el stand devuelve 0
    }
    return stand->ancho * stand->largo; // devuelve el area del stand evualuado
}

// convierte el estado del stand a un dato de tipo string 
const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE:
            return "Disponible";
        case RESERVADO:
            return "Reservado";
        case VENDIDO:
            return "Vendido";
        default:
            return "Desconocido";
    }
}

/* reserva la memoria que se requiere para crear un stand y se le asignan los 
valores correspondientes que debe tener el stand */

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = (Stand *) malloc(sizeof(Stand)); //reserva la memoria necesaria para un stand y asigna la dirrecion a nuevo
    if (nuevo == NULL) {
        return NULL; // memoria insuficiente
    }
 /* asigna los valores a stand */
    nuevo->numero = numero;
    nuevo->ancho = ancho;
    nuevo->largo = largo;
    nuevo->estado = estado;
    nuevo->siguiente = NULL;

    return nuevo; // devuelve el stand creado
}

/* Funcion que inserta un stand en la lista y los ordena por area,
el ordenamiento es de forma ascendente usando de criterio el area de los stands */

void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (cabeza == NULL || nuevo == NULL) { // en caso de que no exista la lista o el stand a insertar, no hace nada
        return;
    }

    float areaNuevo = calcularArea(nuevo);
    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    // Avanza mientras el area actual sea menor o igual a la del nuevo.
    while (actual != NULL && calcularArea(actual) <= areaNuevo) {
        anterior = actual;
        actual = actual->siguiente; //actual apunta al siguiente nodo
    }

    nuevo->siguiente = actual; // el nuevo nodo apunta al nodo actual 

    if (anterior == NULL) {
        *cabeza = nuevo; // el nuevo pasa a ser la cabeza
    } else {
        anterior->siguiente = nuevo; // el anterior nodo ahora apunta al nuevo  
    }
}

/* funcion que busca un stand usando de referencia su numero */
Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza; //

    while (actual != NULL) { // mientras que el nodo actual no sea nulo, seguira buscando en la lista
        if (actual->numero == numero) { // si el numero del nodo actual coincide, se devuelve el nodo actual 
            return actual;
        }
        actual = actual->siguiente; // en caso de que no, se pasa al siguiente nodo
    }

    return NULL; // no encontrado
}


/*funcion que busca el stand por numero, lo desconecta de la lista, actualiza sus datos y
lo vuelve a insertar en dentro de la lista en una nueva posicion */
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    if (cabeza == NULL || *cabeza == NULL) { // si la lista esta vacia, se cancela el proceso
        return 0;
    }

    Stand *actual = *cabeza; 
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) { // mientras que el nodo actual no sea nulo y el numero buscado sea diferente del numero de actual, se sigue la busqueda
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) { // cancela el proceso en caso de que actual sea vacio
        return 0; 
    }

    // Desenganchar el nodo de su posicion actual
    if (anterior == NULL) {
        *cabeza = actual->siguiente; // el nodo siguiente a actual, se vuelve el primero de la lista
    } else {
        anterior->siguiente = actual->siguiente; // desconecta el nodo actual apuntando al siguiente
    }

    // Actualizar los datos
    actual->ancho = ancho;
    actual->largo = largo;
    actual->estado = estado;
    actual->siguiente = NULL;

    // Reinsertar el nodo en su posicion nueva posicion
    insertarOrdenadoPorArea(cabeza, actual);

    return 1;
}

/* Busca el stand por numero, lo desconecta de la lista y libera la memoria reservada */
int borrarStand(Stand **cabeza, int numero) {
    if (cabeza == NULL || *cabeza == NULL) { // si la lista esta vacia, se cancela el proceso
        return 0;
    }

    Stand *actual = *cabeza; 
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) { // se raliza la busqueda del stand por su numero
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return 0; // no encontrado
    }

    if (anterior == NULL) { // si el nodo a eliminar es la cabeza de la lista, se actualiza la cabeza para que apunte al siguiente nodo
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente; // el nodo anterior apunta al siguiente nodo del nodo a eliminar
    }

    free(actual); // libera la memoria del nodo eliminado
    return 1;
}

/* Recorre e imprime la lista de stands junto con todos sus datos */
void imprimirLista(const Stand *cabeza) {
    if (cabeza == NULL) { // si la lista esta vacia, cancela el proceso
        printf("Lista vacia\n");
        return;
    }

    const Stand *actual = cabeza; // accede al primer nodo de la lista
    while (actual != NULL) { // mientras el nodo no sea nulo, se imprmen los datos del nodo actual 
        printf("#%d %.2fx%.2fm area=%.2fm^2 %s\n",
               actual->numero,
               actual->ancho,
               actual->largo,
               calcularArea(actual), 
               estadoAString(actual->estado)); 
        actual = actual->siguiente; // el nodo siguiente a actual, se transforma en el nodo actual
    }
}

/* libera la memoira de todos los nodos de la lista */
void liberarLista(Stand **cabeza) {
    if (cabeza == NULL) { // si la lista esta vacia, cancela el proceso
        return;
    }

    Stand *actual = *cabeza; // accede al primer nodo de la lista
    Stand *siguiente; 

    while (actual != NULL) { // mientras actual no sea nulo, se libera la memoria de actual y se pasa al sigueiente
        siguiente = actual->siguiente;
        free(actual); 
        actual = siguiente; // el nodo siguiente se transforma en el actual
    }

    *cabeza = NULL;
}