#include <stdio.h>
#include <stdlib.h>
#include "stand.h"


int listaVacia(Stand *cabeza) //esta es la funcion extra 
{
    return cabeza == NULL;
}

float calcularArea(const Stand *stand)
{
    return stand->ancho * stand->largo;
}

const char *estadoAString(StandEstado estado)
{
    switch (estado)
    {
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

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado)
{
    Stand *nuevoStand = (Stand *)malloc(sizeof(Stand));

    if (nuevoStand == NULL)
    {
        return NULL;
    }

    nuevoStand->numero = numero;
    nuevoStand->ancho = ancho;
    nuevoStand->largo = largo;
    nuevoStand->estado = estado;
    nuevoStand->siguiente = NULL;

    return nuevoStand;
}

void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo)
{
    Stand *actualptr;
    Stand *anteriorptr = NULL;

    actualptr = *cabeza;

    if (listaVacia(actualptr))
    {
        *cabeza = nuevo;
        return;
    }
    else
    {
        while (actualptr != NULL &&
               calcularArea(nuevo) >= calcularArea(actualptr))
        {
            //se copian las direcciones de memoria correctas
            anteriorptr = actualptr;
            actualptr = actualptr->siguiente;
        }

        if (anteriorptr == NULL)
        {
            //por si es menor incluso que el primero
            *cabeza = nuevo;
            nuevo->siguiente = actualptr;
        }
        else
        {
            //Se le cambian las direcciones de memoria para que este dentro el nuevo nodo
            anteriorptr->siguiente = nuevo;
            nuevo->siguiente = actualptr;
        }
    }
}

Stand *buscarStand(Stand *cabeza, int numero)
{
    Stand *actualptr = cabeza;

    while (actualptr != NULL)
    {
        if (actualptr->numero == numero)
        {
            return actualptr;
        }

        actualptr = actualptr->siguiente;
    }

    return NULL;
}

int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado)
{
    Stand *actualptr = *cabeza;
    Stand *anteriorptr = NULL;

    while (actualptr != NULL)
    {
        if (actualptr->numero == numero)
        {
            if (anteriorptr == NULL)
            {
                *cabeza = actualptr->siguiente;
            }
            else
            {
                anteriorptr->siguiente = actualptr->siguiente;
            }

            actualptr->ancho = ancho;
            actualptr->largo = largo;
            actualptr->estado = estado;
            actualptr->siguiente = NULL;

            insertarOrdenadoPorArea(cabeza, actualptr);

            return 1;
        }

        anteriorptr = actualptr;
        actualptr = actualptr->siguiente;
    }

    return 0;
}

int borrarStand(Stand **cabeza, int numero)
{
    Stand *actualptr = *cabeza;
    Stand *anteriorptr = NULL;

    while (actualptr != NULL)
    {
        if (actualptr->numero == numero)
        {
            if (anteriorptr == NULL)
            {
                *cabeza = actualptr->siguiente;
            }
            else
            {
                anteriorptr->siguiente = actualptr->siguiente;
            }

            free(actualptr);

            return 1;
        }

        anteriorptr = actualptr;
        actualptr = actualptr->siguiente;
    }

    return 0;
}

void imprimirLista(const Stand *cabeza)
{
    if (listaVacia((Stand *)cabeza))
    {
        printf("Lista vacia\n");
        return;
    }

    const Stand *actualptr = cabeza;

    while (actualptr != NULL)
    {
        printf("Stand #%d | Ancho: %.2f | Largo: %.2f | Área: %.2fm^2 | Estado: %s\n",
               actualptr->numero,
               actualptr->ancho,
               actualptr->largo,
               calcularArea(actualptr),
               estadoAString(actualptr->estado));

        actualptr = actualptr->siguiente;
    }
}

void liberarLista(Stand **cabeza)
{
    Stand *actualptr = *cabeza;
    Stand *siguiente;

    while (actualptr != NULL)
    {
        siguiente = actualptr->siguiente;
        free(actualptr);
        actualptr = siguiente;
    }

    *cabeza = NULL;
}
