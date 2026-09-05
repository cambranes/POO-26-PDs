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
    if (estado == DISPONIBLE) {
        return "disponible";
    } else if (estado == RESERVADO) {
        return "reservado";
    } else if (estado == VENDIDO) {
        return "vendido";
    }
    return "desconocido";
}

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = (Stand *)malloc(sizeof(Stand));
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
    if (cabeza == NULL || *cabeza == NULL) {
        return 0;
    }

    Stand *stand = buscarStand(*cabeza, numero);
    if (stand == NULL) {
        return 0;
    }

    float areaVieja = calcularArea(stand);
    float areaNueva = ancho * largo;

    stand->ancho = ancho;
    stand->largo = largo;
    stand->estado = estado;

    if (areaVieja != areaNueva) {
        borrarStand(cabeza, numero);
        Stand *nuevo = crearStand(numero, ancho, largo, estado);
        insertarOrdenadoPorArea(cabeza, nuevo);
    }

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
    printf("lista de stands\n");
    while (actual != NULL) {
        printf("numero: %d | ancho: %.2f | largo: %.2f | area: %.2f | estado: %s\n",
               actual->numero,
               actual->ancho,
               actual->largo,
               calcularArea(actual),
               estadoAString(actual->estado));
        actual = actual->siguiente;
    }
    printf("\n");
}

void liberarLista(Stand **cabeza) {
    if (cabeza == NULL || *cabeza == NULL) {
        return;
    }

    Stand *actual = *cabeza;
    while (actual != NULL) {
        Stand *aux = actual->siguiente;
        free(actual);
        actual = aux;
    }

    *cabeza = NULL;
}