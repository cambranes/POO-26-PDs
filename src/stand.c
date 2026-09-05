#include <stdio.h>
#include <stdlib.h>
#include "stand.h"
 
float calcularArea(const Stand *stand) {
    if (stand == NULL)
        return 0.0f;
 
    return stand->ancho * stand->largo;
}
 
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
 
Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = (Stand *) malloc(sizeof(Stand));
 
    if (nuevo == NULL)
        return NULL;
 
    nuevo->numero = numero;
    nuevo->ancho = ancho;
    nuevo->largo = largo;
    nuevo->estado = estado;
    nuevo->siguiente = NULL;
 
    return nuevo;
}
 
void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (nuevo == NULL)
        return;
 
    float areaNuevo = calcularArea(nuevo);
 
    /* caso 1: la lista esta vacia o el nuevo va antes que la cabeza */
    if (*cabeza == NULL || calcularArea(*cabeza) >= areaNuevo) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }
 
    /* caso 2: recorrer hasta encontrar donde encaja */
    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) < areaNuevo) {
        actual = actual->siguiente;
    }
 
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}
 
Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza;
 
    while (actual != NULL) {
        if (actual->numero == numero)
            return actual;
        actual = actual->siguiente;
    }
 
    return NULL;
}
 
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    Stand *actual = *cabeza;
    Stand *anterior = NULL;
 
    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }
 
    if (actual == NULL)
        return 0; /* no existe ese numero de stand */
 
    /* como el area puede cambiar, sacamos el nodo de la lista y lo
       volvemos a insertar para que quede en su nueva posicion ordenada */
    if (anterior == NULL)
        *cabeza = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;
 
    actual->ancho = ancho;
    actual->largo = largo;
    actual->estado = estado;
    actual->siguiente = NULL;
 
    insertarOrdenadoPorArea(cabeza, actual);
 
    return 1;
}
 
int borrarStand(Stand **cabeza, int numero) {
    Stand *actual = *cabeza;
    Stand *anterior = NULL;
 
    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }
 
    if (actual == NULL)
        return 0; /* no se encontro */
 
    if (anterior == NULL)
        *cabeza = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;
 
    free(actual);
    return 1;
}
 
void imprimirLista(const Stand *cabeza) {
    const Stand *actual = cabeza;
 
    if (actual == NULL) {
        printf("(lista vacia)\n");
        return;
    }
 
    while (actual != NULL) {
        printf("Stand #%d - %.2fm x %.2fm - Area: %.2fm^2 - %s\n",
               actual->numero, actual->ancho, actual->largo,
               calcularArea(actual), estadoAString(actual->estado));
        actual = actual->siguiente;
    }
}
 
void liberarLista(Stand **cabeza) {
    Stand *actual = *cabeza;
    Stand *siguiente;
 
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
 
    *cabeza = NULL;
}