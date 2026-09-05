#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

/* Calcula el área de un stand */
float calcularArea(const Stand *stand) {
    if (stand == NULL) {
        return 0.0f;
    }

    return stand->ancho * stand->largo;
}

/* Convierte un estado a cadena de texto */
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

/* Crea un nuevo stand en memoria dinamica */
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

/* Inserta un stand manteniendo la lista ordenada por area */
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

/* Busca un stand por numero */
Stand *buscarStand(Stand *cabeza, int numero) {
    while (cabeza != NULL) {
        if (cabeza->numero == numero) {
            return cabeza;
        }

        cabeza = cabeza->siguiente;
    }
    return NULL;
}

/* Actualiza un stand y reordena la lista */
int actualizarStand(
    Stand **cabeza,
    int numero,
    float ancho,
    float largo,
    StandEstado estado
) {
    Stand *actual;
    Stand *anterior = NULL;

    if (cabeza == NULL || *cabeza == NULL) {
        return 0;
    }

    actual = *cabeza;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return 0;
    }

    /* Desconectar nodo */
    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    /* Actualizar datos */
    actual->ancho = ancho;
    actual->largo = largo;
    actual->estado = estado;
    actual->siguiente = NULL;

    /* Reinsertar ordenadamente */
    insertarOrdenadoPorArea(cabeza, actual);

    return 1;
}

/* Elimina un stand de la lista */
int borrarStand(Stand **cabeza, int numero) {
    Stand *actual;
    Stand *anterior = NULL;

    if (cabeza == NULL || *cabeza == NULL) {
        return 0;
    }

    actual = *cabeza;

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

/* Imprime todos los stands */
void imprimirLista(const Stand *cabeza) {
    if (cabeza == NULL) {
        printf("Lista vacía.\n");
        return;
    }

    while (cabeza != NULL) {
        printf(
            "Stand #%d | %.2f x %.2f | Área: %.2f m² | Estado: %s\n",
            cabeza->numero,
            cabeza->ancho,
            cabeza->largo,
            calcularArea(cabeza),
            estadoAString(cabeza->estado)
        );

        cabeza = cabeza->siguiente;
    }
}

/* Libera toda la memoria de la lista */
void liberarLista(Stand **cabeza) {
    Stand *temp;

    if (cabeza == NULL) {
        return;
    }

    while (*cabeza != NULL) {
        temp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(temp);
    }
}