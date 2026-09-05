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
    Stand *actual;

    if (cabeza == NULL || nuevo == NULL) {
        return;
    }

    if (*cabeza == NULL ||
        calcularArea(nuevo) < calcularArea(*cabeza)) {

        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    actual = *cabeza;

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

int actualizarStand(Stand **cabeza, int numero, float ancho,
                    float largo, StandEstado estado) {
    Stand *stand;
    Stand *anterior;

    if (cabeza == NULL) {
        return 0;
    }

    stand = buscarStand(*cabeza, numero);

    if (stand == NULL) {
        return 0;
    }

    /*
     * Primero se quita el nodo de su posición actual porque
     * el cambio de dimensiones puede modificar su área.
     */
    if (*cabeza == stand) {
        *cabeza = stand->siguiente;
    } else {
        anterior = *cabeza;

        while (anterior->siguiente != NULL &&
               anterior->siguiente != stand) {
            anterior = anterior->siguiente;
        }

        if (anterior->siguiente == NULL) {
            return 0;
        }

        anterior->siguiente = stand->siguiente;
    }

    stand->ancho = ancho;
    stand->largo = largo;
    stand->estado = estado;
    stand->siguiente = NULL;

    /* Se vuelve a insertar para mantener el orden por área. */
    insertarOrdenadoPorArea(cabeza, stand);

    return 1;
}

int borrarStand(Stand **cabeza, int numero) {
    Stand *actual;
    Stand *anterior;

    if (cabeza == NULL || *cabeza == NULL) {
        return 0;
    }

    actual = *cabeza;

    if (actual->numero == numero) {
        *cabeza = actual->siguiente;
        free(actual);
        return 1;
    }

    anterior = actual;
    actual = actual->siguiente;

    while (actual != NULL) {
        if (actual->numero == numero) {
            anterior->siguiente = actual->siguiente;
            free(actual);
            return 1;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    return 0;
}

void imprimirLista(const Stand *cabeza) {
    const Stand *actual = cabeza;

    if (actual == NULL) {
        printf("Lista vacia.\n");
        return;
    }

    while (actual != NULL) {
        printf("Stand #%d | %.2fm x %.2fm | Area: %.2fm^2 | Estado: %s\n",
               actual->numero,
               actual->ancho,
               actual->largo,
               calcularArea(actual),
               estadoAString(actual->estado));

        actual = actual->siguiente;
    }
}

void liberarLista(Stand **cabeza) {
    Stand *actual;
    Stand *siguiente;

    if (cabeza == NULL) {
        return;
    }

    actual = *cabeza;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    *cabeza = NULL;
}