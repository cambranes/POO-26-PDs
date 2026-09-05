#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

//Calcular el área de un stand
float calcularArea(const Stand *stand) {
    if (stand == NULL) {
        return 0.0f;
    }
    return stand->ancho * stand->largo;//Realiza el calculo del area
}

//Convertir el estado a una cadena de texto (string)
const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE:
            return "DISPONIBLE";
        case RESERVADO:
            return "RESERVADO";
        case VENDIDO:
            return "VENDIDO";
        default:
            return "DESCONOCIDO";
    }
}

//Crear e inicializa un nuevo stand mediante memoria dinámica
Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = (Stand*)malloc(sizeof(Stand));//Reserva memoria para guardar un stand
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

//Insertar los stands de menor a mayor
void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (nuevo == NULL || cabeza == NULL) return;

    //Lista vacía o el nuevo tiene menor área que el primero
    if (*cabeza == NULL || calcularArea(nuevo) < calcularArea(*cabeza)) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    //Recorrer la lista para encontrar su posición correcta
    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) <= calcularArea(nuevo)) {
        actual = actual->siguiente;
    }
    
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

//Busca un stand por su ID
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

//Actualizar los datos de un stand existente(La lista no puede ser vacia )
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    if (cabeza == NULL || *cabeza == NULL) return 0;

    //Buscar si el stand existe
    Stand *standAEditar = buscarStand(*cabeza, numero);
    if (standAEditar == NULL) {
        return 0; // No se encontró
    }

    Stand *actual = *cabeza;
    Stand *anterior = NULL;
    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    //Asignar los nuevos valores
    standAEditar->ancho = ancho;
    standAEditar->largo = largo;
    standAEditar->estado = estado;
    standAEditar->siguiente = NULL;

    //Inserta los nuevos datos del stand
    insertarOrdenadoPorArea(cabeza, standAEditar);
    return 1;
}

//Elimina un stand mediante su ID
int borrarStand(Stand **cabeza, int numero) {
    if (cabeza == NULL || *cabeza == NULL) return 0;

    Stand *actual = *cabeza;
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return 0; // No encontrado
    }

    if (anterior == NULL) {
        // Es el primer elemento de la lista
        *cabeza = actual->siguiente;
    } else {
        // Está en medio o al final
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    return 1;
}

//Imprime la lista de los stands
void imprimirLista(const Stand *cabeza) {
    printf("\n                    LISTA DE STANDS\n");
    printf("----------------------------------------------------------\n");

    if (cabeza == NULL) {
        printf("La lista esta vacia.\n");
    } else {
        const Stand *actual = cabeza;
        while (actual != NULL) {
            printf("Numero: %d | Ancho: %.2f m | Largo: %.2f m | Area: %.2f m2 | Estado: %s\n",
                   actual->numero,
                   actual->ancho,
                   actual->largo,
                   calcularArea(actual),
                   estadoAString(actual->estado));
            actual = actual->siguiente;
        }
    }
    printf("----------------------------------------------------------\n");
}

//Libera la memoria dinámica asignada para los stands
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

