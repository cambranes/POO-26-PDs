#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

float calcularArea(const Stand *stand) {
    if (stand == NULL) return 0.0f;
    return stand->ancho * stand->largo;
}
  
const char *estadoAString(StandEstado estado) {
      switch (estado) {
        case DISPONIBLE:
            return "DISPONIBLE";
        case RESERVADO:
            return "RESERVADO";
        case VENDIDO:
            return "VENDIDO";
    }
    return "";
}

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
   Stand *nuevo = (Stand *)malloc(sizeof(Stand));
    if (nuevo == NULL) {
        printf("Error: Memoria insuficiente.\n");
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
    if (nuevo == NULL) return;

    if (*cabeza == NULL || calcularArea(nuevo) < calcularArea(*cabeza)) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) <= calcularArea(nuevo)) {
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

    if (borrarStand(cabeza, numero)) {
        Stand *nuevo = crearStand(numero, ancho, largo, estado);
        if (nuevo == NULL) return 0;
        insertarOrdenadoPorArea(cabeza, nuevo);
        return 1;
    }

    return 0;
}

int borrarStand(Stand **cabeza, int numero) {
    if (cabeza == NULL || *cabeza == NULL) return 0;

    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) return 0;

    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    return 1;
}
void imprimirLista(const Stand *cabeza) {
   if (cabeza == NULL) {
        printf("Sin registros almacenados.\n");
        return;
    }

    const Stand *aux = cabeza;
    while (aux != NULL) {
        printf("\nN° Puesto: %d\n", aux->numero);
        printf("Dimensiones: %.2f m x %.2f m\n", aux->ancho, aux->largo);
        printf("Superficie: %.2f m2\n", calcularArea(aux));
        printf("Situacion: %s\n", estadoAString(aux->estado));
        aux = aux->siguiente;
    }
}

void liberarLista(Stand **cabeza) {
   if (cabeza == NULL) return;

    Stand *actual = *cabeza;
    Stand *siguiente;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    *cabeza = NULL;
}
