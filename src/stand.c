#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

// Calcula el área al vuelo ya que no está guardada en la estructura
float calcularArea(const Stand *stand) {
    if (stand == NULL) return 0.0;
    return stand->ancho * stand->largo;
}

// Convierte el estado Enum a cadena para la impresión
const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE: return "Disponible";
        case RESERVADO: return "Reservado";
        case VENDIDO: return "Vendido";
        default: return "Desconocido";
    }
}

// Reserva memoria dinámica para un nuevo stand
Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = (Stand *)malloc(sizeof(Stand));
    if (nuevo == NULL) {
        printf("Error: Fallo la asignacion de memoria.\n");
        exit(1);
    }
    nuevo->numero = numero;
    nuevo->ancho = ancho;
    nuevo->largo = largo;
    nuevo->estado = estado;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Inserta el nodo ya creado en la posición correcta según su área (menor a mayor)
void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (nuevo == NULL) return;

    float areaNuevo = calcularArea(nuevo);

    // Caso 1: Lista vacía o el nuevo nodo debe ir al principio
    if (*cabeza == NULL || calcularArea(*cabeza) >= areaNuevo) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    // Caso 2: Recorrer para ubicar la posición correcta
    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) < areaNuevo) {
        actual = actual->siguiente;
    }

    // Enlazamos
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

// Busca un stand por su identificador. Retorna NULL si no existe
Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza;
    while (actual != NULL) {
        if (actual->numero == numero) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

// Actualiza un stand. Si cambian sus dimensiones, lo desvincula y lo reinserta
// para mantener el ordenamiento correcto de la lista.
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    // Buscar el nodo y su anterior
    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) return 0; // No se encontró el stand

    float areaActual = calcularArea(actual);
    float nuevaArea = ancho * largo;

    // Si el área va a cambiar, se debe reubicar el nodo en la lista
    if (areaActual != nuevaArea) {
        // 1. Desvincular el nodo de su posición actual
        if (anterior == NULL) {
            *cabeza = actual->siguiente; // Era el primer nodo
        } else {
            anterior->siguiente = actual->siguiente;
        }

        // 2. Actualizar datos
        actual->ancho = ancho;
        actual->largo = largo;
        actual->estado = estado;
        actual->siguiente = NULL; // Limpiamos su puntero

        // 3. Reinsertar el nodo para respetar el orden
        insertarOrdenadoPorArea(cabeza, actual);
    } else {
        // Si el área no cambia (ej. solo cambió estado, o dimensiones invertidas 2x3 -> 3x2)
        actual->ancho = ancho;
        actual->largo = largo;
        actual->estado = estado;
    }

    return 1; // Éxito
}

// Borra un stand, liberando su memoria dinámica
int borrarStand(Stand **cabeza, int numero) {
    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) return 0; // No encontrado

    // Desvincular
    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual); // Liberar memoria
    return 1; // Éxito
}

// Imprime el inventario con formato
void imprimirLista(const Stand *cabeza) {
    printf("--- INVENTARIO FILEY (Ordenado por area) ---\n");
    const Stand *actual = cabeza;
    if (actual == NULL) {
        printf("La lista esta vacia.\n");
    } else {
        while (actual != NULL) {
            printf("Stand #%d | Area: %.2f m2 (%.2fm x %.2fm) | Estado: %s\n",
                   actual->numero, calcularArea(actual), actual->ancho, actual->largo,
                   estadoAString(actual->estado));
            actual = actual->siguiente;
        }
    }
    printf("--------------------------------------------\n\n");
}

// Libera toda la lista y previene fugas de memoria
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