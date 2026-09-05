#include <stdio.h>
#include <stdlib.h>
#include "stand.h"

// ancho * largo, la calculamos aparte porque se usa en varios lados
float calcularArea(const Stand *stand) {
    return stand->ancho * stand->largo;
}

// convierte el enum a texto para que se vea bien en consola
const char *estadoAString(StandEstado estado) {
    if (estado == DISPONIBLE) return "Disponible";
    if (estado == RESERVADO) return "Reservado";
    if (estado == VENDIDO) return "Vendido";
    return "Desconocido";
}

// arma el nodo en memoria dinamica, no lo inserta todavia
Stand *crearStand(int numero, float ancho, float largo, StandEstado estado) {
    Stand *nuevo = malloc(sizeof(Stand));
    if (nuevo == NULL) {
        printf("no hay memoria\n");
        return NULL;
    }

    nuevo->numero = numero;
    nuevo->ancho = ancho;
    nuevo->largo = largo;
    nuevo->estado = estado;
    nuevo->siguiente = NULL;

    return nuevo;
}

// inserta el nodo en el lugar que le toca segun su area, no al final
void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo) {
    if (nuevo == NULL) return;

    float area = calcularArea(nuevo);

    // va primero si la lista esta vacia o si su area es menor que la del primero
    if (*cabeza == NULL || area < calcularArea(*cabeza)) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }

    // si no, buscamos el nodo justo antes de donde debe quedar
    Stand *actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) <= area) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

// busqueda lineal por numero, devuelve el nodo o NULL si no esta
Stand *buscarStand(Stand *cabeza, int numero) {
    Stand *actual = cabeza;
    while (actual != NULL) {
        if (actual->numero == numero) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

// si cambia ancho o largo, el area cambia y el nodo puede quedar mal ubicado
// en la lista ordenada, asi que en vez de editar en el lugar, lo borramos
// y lo insertamos de nuevo ya con los datos actualizados
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado) {
    Stand *encontrado = buscarStand(*cabeza, numero);
    if (encontrado == NULL) {
        printf("no existe el stand %d\n", numero);
        return 0;
    }

    borrarStand(cabeza, numero);
    Stand *nuevo = crearStand(numero, ancho, largo, estado);
    insertarOrdenadoPorArea(cabeza, nuevo);
    return 1;
}

// borra por numero, contemplando el caso de que sea la cabeza o un nodo intermedio
int borrarStand(Stand **cabeza, int numero) {
    if (*cabeza == NULL) {
        printf("la lista esta vacia\n");
        return 0;
    }

    if ((*cabeza)->numero == numero) {
        Stand *viejo = *cabeza;
        *cabeza = viejo->siguiente;
        free(viejo);
        return 1;
    }

    Stand *anterior = *cabeza;
    Stand *actual = (*cabeza)->siguiente;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("no existe el stand %d\n", numero);
        return 0;
    }

    anterior->siguiente = actual->siguiente;
    free(actual);
    return 1;
}

// recorre e imprime, ya sale ordenado por area de menor a mayor
void imprimirLista(const Stand *cabeza) {
    if (cabeza == NULL) {
        printf("la lista esta vacia\n");
        return;
    }

    const Stand *actual = cabeza;
    while (actual != NULL) {
        printf("numero %d, ancho %.2f, largo %.2f, area %.2f, estado %s\n",
               actual->numero, actual->ancho, actual->largo,
               calcularArea(actual), estadoAString(actual->estado));
        actual = actual->siguiente;
    }
}

// libera todos los nodos y deja la cabeza en NULL para evitar punteros colgados
void liberarLista(Stand **cabeza) {
    Stand *actual = *cabeza;
    while (actual != NULL) {
        Stand *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}