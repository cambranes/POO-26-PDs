#include <stdio.h>
#include <stdlib.h> //gestion memoria dinamic
#include <string.h> // para cadenas de texto
#include "stand.h"

float calcularArea(const Stand *stand) {
    if (stand == NULL) return 0.0f;
    return stand->ancho * stand->largo;
}

const char *estadoAString(StandEstado estado) { //convierte el numero a texto para el usuario
    if (estado == DISPONIBLE) {
        return "Disponible";
    }
    return "Ocupado";
}

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) { //la funcion va a devolver la direccion de memoria
    Stand *nuevo = (Stand *) malloc(sizeof(Stand)); //reservamos memoria para un nuevo nodo
    if (nuevo != NULL) {
        nuevo->numero = numero;
        nuevo->ancho = ancho;
        nuevo->largo = largo;
        nuevo->estado = estado;
        nuevo->siguiente = NULL; //inicializamos el puntero siguiente a NULL
    }
    return nuevo;
}

void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (nuevo == NULL || cabeza == NULL) return;

    float areaNuevo = calcularArea(nuevo);

    if (*cabeza == NULL || calcularArea(*cabeza) > areaNuevo) { // caso Lista vacia o area del nuevo es menor a head
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) <= areaNuevo) { //recorrido para buscar su lugar
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza;
    while (actual != NULL) {
        if (actual->numero == numero) {
            return actual; //si encontramos el stand con el id buscado
        }
        actual = actual->siguiente;
    }
    return NULL; //si no encontramos el stand con el id buscado
}

int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    if (cabeza == NULL) return 0;

    Stand *encontrado = buscarStand(*cabeza, numero);
    if (encontrado != NULL) {
        encontrado->ancho = ancho;
        encontrado->largo = largo;
        encontrado->estado = estado;
        printf("El stand %d ha sido actualizado.\n", numero);
        return 1;
    } else {
        printf("El stand %d no fue encontrado.\n", numero);
        return 0;
    }
}

int borrarStand(Stand **cabeza, int numero) {
    if (cabeza == NULL || *cabeza == NULL) return 0; //no hay nada que buscar

    if ((*cabeza)->numero == numero) { //si el primer nodo es el que queremos borrar
        Stand *temp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(temp);
        printf("El stand %d ha sido borrado.\n", numero);
        return 1;
    }

    Stand *actual = *cabeza; //borrar nodo de enmedio o al final
    while (actual->siguiente != NULL && actual->siguiente->numero != numero) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != NULL) {
        Stand *temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        free(temp);
        printf("El stand %d ha sido borrado.\n", numero);
        return 1;
    } else {
        printf("El stand %d no fue encontrado.\n", numero);
        return 0;
    }
}

void imprimirLista(const Stand *cabeza) {
    const Stand *actual = cabeza;
    if (actual == NULL) {
        printf("La lista esta vacia\n");
        return;
    }
    printf("Lista de stands:\n");
    while (actual != NULL) {
        printf("ID: %d, Dimensiones: %.2fm2, Estado: %s\n", actual->numero, calcularArea(actual), estadoAString(actual->estado));
        actual = actual->siguiente;
    }
}

void liberarLista(Stand **cabeza) {
    if (cabeza == NULL) return;

    Stand *actual = *cabeza;
    Stand *sig;
    while (actual != NULL) {
        sig = actual->siguiente;
        free(actual);
        actual = sig;
    }
    *cabeza = NULL;
    printf("Memoria liberada.\n");
}