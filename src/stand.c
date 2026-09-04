#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

float calcularArea(const Stand *stand) {
    if (stand == NULL) return 0.0f;
    return stand->ancho * stand->largo;
}

const char *estadoAString(StandEstado estado) {
    if (estado == DISPONIBLE) return "Disponible";
    if (estado == RESERVADO) return "Reservado";
    if (estado == VENDIDO) return "Vendido";
    return "Desconocido";
}

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = (Stand *)malloc(sizeof(Stand));
    if (nuevo != NULL) {
        nuevo->numero = numero;
        nuevo->ancho = ancho;
        nuevo->largo = largo;
        nuevo->estado = estado;
        nuevo->siguiente = NULL;
    }
    return nuevo;
}

void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (cabeza == NULL || nuevo == NULL) return;

    float areaNuevo = calcularArea(nuevo);

    if (*cabeza == NULL || areaNuevo < calcularArea(*cabeza)) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) <= areaNuevo) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza;
    while (actual != NULL) {
        if (actual->numero == numero) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    if (cabeza == NULL || *cabeza == NULL) return 0;

    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) return 0; 
    float areaAntigua = calcularArea(actual);
    float areaNueva = ancho * largo;

    if (areaAntigua != areaNueva) {
  
        if (anterior == NULL) {
            *cabeza = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
        actual->siguiente = NULL;

   
        actual->ancho = ancho;
        actual->largo = largo;
        actual->estado = estado;


        insertarOrdenadoPorArea(cabeza, actual);
    } else {
     
        actual->ancho = ancho;
        actual->largo = largo;
        actual->estado = estado;
    }

    return 1; 
}

int borrarStand(Stand **cabeza, int numero) {
    if (cabeza == NULL || *cabeza == NULL) return 0;

    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    if (actual->numero == numero) {
        *cabeza = actual->siguiente;
        free(actual);
        return 1;
    }

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) return 0; 

    anterior->siguiente = actual->siguiente;
    free(actual);
    return 1;
}

void imprimirLista(const Stand *cabeza) {
    if (cabeza == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    const Stand *actual = cabeza;
    while (actual != NULL) {
        printf("Stand #%d | Area: %.2f m2 (%.2fm x %.2fm) | Estado: %s\n",
               actual->numero, calcularArea(actual), actual->ancho, actual->largo, estadoAString(actual->estado));
        actual = actual->siguiente;
    }
}

void liberarLista(Stand **cabeza) {
    if (cabeza == NULL || *cabeza == NULL) return;
    
    Stand *actual = *cabeza;
    Stand *siguiente;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    
    *cabeza = NULL;
}