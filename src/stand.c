#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

float calcularArea(const Stand *stand) {
        if (stand == NULL) {
        return 0.0f;
        }
    return stand->ancho * stand->largo;
   }

const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE:
            return "Disponible";   case RESERVADO:
            return "Reservado";
        case VENDIDO:
            return "Vendido";
        default:
            return "Desconocido";}
    
    }

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
   Stand *nuevo = malloc(sizeof(Stand));

    if (nuevo == NULL) {
        return NULL;
    }

    nuevo->numero = numero;
    nuevo->ancho = ancho;
    nuevo->largo = largo;
    nuevo->estado = estado;
    nuevo->siguiente = NULL;

    return nuevo;
    }

void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (cabeza == NULL || nuevo == NULL) {
        return;
    }

    if (*cabeza == NULL ||
        calcularArea(nuevo) < calcularArea(*cabeza)) {

        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    Stand *actual = *cabeza;

    while (actual->siguiente != NULL &&
           calcularArea(actual->siguiente) <= calcularArea(nuevo)) {
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

int actualizarStand(Stand **cabeza, int numero,
                    float ancho, float largo, StandEstado estado) {
    if (cabeza == NULL || *cabeza == NULL) {
        return 0;
    }

    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return 0;
    }

    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    actual->ancho = ancho;
    actual->largo = largo;
    actual->estado = estado;
    actual->siguiente = NULL;

    insertarOrdenadoPorArea(cabeza, actual);

    return 1;
    }

int borrarStand(Stand **cabeza, int numero) {
    if (cabeza == NULL || *cabeza == NULL) {
        return 0;
    }

    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return 0;
    }

    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);

    return 1;
}

void imprimirLista(const Stand *cabeza) {
    const Stand *actual = cabeza;

    while (actual != NULL) {
        printf("Stand #%d | Ancho: %.2f | Largo: %.2f | "
               "Área: %.2f m^2 | Estado: %s\n",
               actual->numero,
               actual->ancho,
               actual->largo,
               calcularArea(actual),
               estadoAString(actual->estado));

        actual = actual->siguiente;
    }
}

void liberarLista(Stand **cabeza) {
    if (cabeza == NULL) {
        return;
    }

    Stand *actual = *cabeza;

    while (actual != NULL) {
        Stand *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    *cabeza = NULL;
    }