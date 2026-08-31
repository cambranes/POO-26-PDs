#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

// calculte the area of a stand (width x length)
float calcularArea(const Stand *stand) {
    if (stand == NULL)
    {
        return 0.0f;
    }
    return stand->ancho * stand->largo;
}

// convert the stand status to a string representation
const char *estadoAString(StandEstado estado) {
    switch (estado)
    {
    case DISPONIBLE:
        return "Disponible";
    case RESERVADO:
        return "Reservado";
    case VENDIDO:
        return "Vendido";
    default:
        return "Unknown";
    }
}

// create a new stand with dynamic memory allocation
Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = (Stand *)malloc(sizeof(Stand));

    if (nuevo == NULL)
    {
        return NULL;
    }

    // init the stand's attributes
    nuevo->numero = numero;
    nuevo->ancho = ancho;
    nuevo->largo = largo;
    nuevo->estado = estado;
    nuevo->siguiente = NULL;

    return nuevo;
}

// insert a stand in the list ordered by area
// the  list maintains ascending order of areas
void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (nuevo == NULL)
    {
        return;
    }

    // if the list is empty or the new stand has smaller area
    if (*cabeza == NULL || calcularArea(nuevo) < calcularArea(*cabeza))
    {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    // actually find the correct position to insert the new stand
    Stand *actual = *cabeza;
    float areaNew = calcularArea(nuevo);

    while (actual->siguiente != NULL && calcularArea(actual->siguiente) < areaNew)
    {
        actual = actual->siguiente;
    }

    // insert the new stand between 'actual' and 'actual->siguiente'
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

// search for a stand by its number
Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza;

    while (actual != NULL)
    {
        if (actual->numero == numero)
        {
            return actual;
        }
        actual = actual->siguiente;
    }

    return NULL; // when the stand is not found
}

// updates a stand's dimensions and status
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    Stand *stand = buscarStand(*cabeza, numero);

    if (stand == NULL)
    {
        return 0; // stand not found
    }

    float areaAntigua = calcularArea(stand);
    float areanueva = ancho * largo;

    // if area hasn't changed, just update the attributes
    if (areaAntigua == areanueva)
    {
        stand->ancho = ancho;
        stand->largo = largo;
        stand->estado = estado;
        return 1;
    }

    // if area has changed, well removes the stand from the list and re-insert it ordered
    if (borrarStand(cabeza, numero))
    {
        Stand *stanActualizado = crearStand(numero, ancho, largo, estado);
        if (stanActualizado != NULL)
        {
            insertarOrdenadoPorArea(cabeza, stanActualizado);
            return 1;
        }
    }

    return 0;
}

// remove a stand from the list and free its memory
int borrarStand(Stand **cabeza, int numero)
{
    if (*cabeza == NULL)
    {
        return 0;
    }

    // if the stand to delete is the head of the list
    if ((*cabeza)->numero == numero)
    {
        Stand *temp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(temp);
        return 1;
    }

    // finnnd the stand and its previous node
    Stand *actual = *cabeza;

    while (actual->siguiente != NULL)
    {
        if (actual->siguiente->numero == numero)
        {
            Stand *temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            free(temp);
            return 1;
        }
        actual = actual->siguiente;
    }

    return 0; // stand not found
}

// print all stands in the list with their info
void imprimirLista(const Stand *cabeza) {
    if (cabeza == NULL)
    {
        printf("La lista esta vacia\n");
        return;
    }

    const Stand *actual = cabeza;

    while (actual != NULL)
    {
        printf("Stand #%d - Area: %.2f m2 - Ancho: %.2f - Largo: %.2f - Estado: %s\n",
               actual->numero,
               calcularArea(actual),
               actual->ancho,
               actual->largo,
               estadoAString(actual->estado));
        actual = actual->siguiente;
    }
}

// free all memory allocated for the list
void liberarLista(Stand **cabeza) {
    Stand *actual = *cabeza;

    while (actual != NULL)
    {
        Stand *temp = actual;
        actual = actual->siguiente;
        free(temp); // free each node
    }

    *cabeza = NULL; // set the head pointer to NULL
}
