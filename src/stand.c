#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

// Calcula y retorna el área del stand
float calcularArea(const Stand *stand) {
    if (stand == NULL) return 0.0f;
    return stand->ancho * stand->largo;
}

// Retorna una cadena de texto según el estado para facilitar la impresión
const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE: return "Disponible";
        case RESERVADO:  return "Reservado";
        case VENDIDO:    return "Vendido";
        default:         return "Desconocido";
    }
}

// Asigna memoria dinámica para un nuevo stand y lo inicializa
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

// Inserta un nodo manteniendo la lista ordenada de menor a mayor área
void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (nuevo == NULL) return;

    float areaNuevo = calcularArea(nuevo);

    // Caso 1: Lista vacía o el nuevo nodo tiene un área menor o igual al primero
    if (*cabeza == NULL || calcularArea(*cabeza) >= areaNuevo) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    // Caso 2: Buscar la posición correcta en el resto de la lista
    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) < areaNuevo) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

// Busca un stand por su número identificador
Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza;
    while (actual != NULL) {
        if (actual->numero == numero) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; // No se encontró
}

// Actualiza los datos. Si el área cambia, reordena la lista.
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    Stand *objetivo = buscarStand(*cabeza, numero);
    if (objetivo == NULL) {
        return 0; 
    }

    float areaActual = calcularArea(objetivo);
    float nuevaArea = ancho * largo;

    if (areaActual == nuevaArea) {
        // Si el área no cambia, los actualizamos directamente
        objetivo->ancho = ancho;
        objetivo->largo = largo;
        objetivo->estado = estado;
        return 1;
    }

    // Si el área cambia, se debe reordenar el nodo para mantener la integridad de la lista
    borrarStand(cabeza, numero);
    Stand *nuevo = crearStand(numero, ancho, largo, estado);
    insertarOrdenadoPorArea(cabeza, nuevo);

    return 1;
}

// Elimina un stand de la lista y libera su memoria. (Corregido a Stand **cabeza)
int borrarStand(Stand **cabeza, int numero) {
    if (*cabeza == NULL) return 0;

    Stand *temp = NULL;

    // Caso 1: El nodo a borrar es el primero
    if ((*cabeza)->numero == numero) {
        temp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(temp);
        return 1;
    }

    // Caso 2: El nodo a borrar está en el medio o al final
    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && actual->siguiente->numero != numero) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != NULL) {
        temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        free(temp); 
        return 1;
    }

    return 0; // El stand no existía
}

// Recorre e imprime los datos de la lista
void imprimirLista(const Stand *cabeza) {
    const Stand *actual = cabeza;
    printf("\n--- Lista de Stands ---\n");
    if (actual == NULL) {
        printf("La lista esta vacia.\n");
    }
    while (actual != NULL) {
        printf("Stand #%d | Area: %5.2fm^2 (%4.2fm x %4.2fm) | Estado: %s\n",
               actual->numero,
               calcularArea(actual),
               actual->ancho,
               actual->largo,
               estadoAString(actual->estado));
        actual = actual->siguiente;
    }
    printf("-----------------------\n");
}

// Libera toda la memoria dinámica de los nodos de la lista
void liberarLista(Stand **cabeza) {
    Stand *actual = *cabeza;
    Stand *siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}