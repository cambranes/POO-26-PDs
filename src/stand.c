#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

// Calcula el area del stand
float calcularArea(const Stand *stand) {
    if (stand == NULL) return 0.0f;
    return stand->ancho * stand->largo;
}

// Convierte el enum del estado a una cadena de texto
const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE: return "Disponible";
        case RESERVADO:  return "Reservado";
        case VENDIDO:    return "Vendido";
        default:         return "Desconocido";
    }
}

// Crea e inicializa un nuevo nodo Stand en memoria dinamica (heap)
Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *n = (Stand *)malloc(sizeof(Stand));
    if (n == NULL) {
        printf("Error: memoria insuficiente\n");
        return NULL;
    }
    n->numero = numero;
    n->ancho = ancho;
    n->largo = largo;
    n->estado = estado;
    n->siguiente = NULL;
    return n;
}

// Inserta un nodo de forma ordenada según su área (menor a mayor)
void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (cabeza == NULL || nuevo == NULL) return;

    float a_nuev = calcularArea(nuevo);

    // Insertar al inicio si la lista esta vacia o tiene menor area
    if (*cabeza == NULL || a_nuev < calcularArea(*cabeza)) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    Stand *act = *cabeza;
    while (act->siguiente != NULL && calcularArea(act->siguiente) <= a_nuev) {
        act = act->siguiente;
    }

    nuevo->siguiente = act->siguiente;
    act->siguiente = nuevo;
}

// Busca un stand por su número ID
Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *act = cabeza;
    while (act != NULL) {
        if (act->numero == numero) return act;
        act = act->siguiente;
    }
    return NULL;
}

// Actualiza las dimensiones y estado de un stand; reordena la lista si cambia su área
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    if (cabeza == NULL || *cabeza == NULL) return 0;

    Stand *st = buscarStand(*cabeza, numero);
    if (st == NULL) return 0;

    float a_ant = calcularArea(st);
    st->ancho = ancho;
    st->largo = largo;
    st->estado = estado;
    float a_nuev = calcularArea(st);

    // Si el area cambio, se remueve y reinserta para mantener el orden
    if (a_ant != a_nuev) {
        // Desvincular de la lista
        if ((*cabeza)->numero == numero) {
            *cabeza = st->siguiente;
        } else {
            Stand *prev = *cabeza;
            while (prev->siguiente != NULL && prev->siguiente->numero != numero) {
                prev = prev->siguiente;
            }
            if (prev->siguiente != NULL) {
                prev->siguiente = st->siguiente;
            }
        }
        st->siguiente = NULL;
        insertarOrdenadoPorArea(cabeza, st);
    }
    return 1;
}

// Borra un stand por su número liberando su memoria
int borrarStand(Stand **cabeza, int numero) {
    if (cabeza == NULL || *cabeza == NULL) return 0;

    Stand *temp;
    // Si esta en la cabeza
    if ((*cabeza)->numero == numero) {
        temp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(temp);
        return 1;
    }

    Stand *act = *cabeza;
    while (act->siguiente != NULL && act->siguiente->numero != numero) {
        act = act->siguiente;
    }

    if (act->siguiente != NULL) {
        temp = act->siguiente;
        act->siguiente = temp->siguiente;
        free(temp);
        return 1;
    }

    return 0;
}

// Imprime el contenido de la lista
void imprimirLista(const Stand *cabeza) {
    const Stand *act = cabeza;
    printf("----------------------------------------------------------\n");
    printf("| Numero | Ancho(m) | Largo(m) | Area(m2) |    Estado    |\n");
    printf("----------------------------------------------------------\n");
    while (act != NULL) {
        printf("| %-6d | %-8.2f | %-8.2f | %-8.2f | %-12s |\n",
               act->numero, act->ancho, act->largo, calcularArea(act), estadoAString(act->estado));
        act = act->siguiente;
    }
    printf("----------------------------------------------------------\n\n");
}

// Libera toda la memoria asignada a la lista
void liberarLista(Stand **cabeza) {
    if (cabeza == NULL) return;

    Stand *act = *cabeza;
    Stand *sig;
    while (act != NULL) {
        sig = act->siguiente;
        free(act);
        act = sig;
    }
    *cabeza = NULL;
}