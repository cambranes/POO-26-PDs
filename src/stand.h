#ifndef STAND_H
#define STAND_H

typedef enum {
    DISPONIBLE = 0,
    RESERVADO,
    VENDIDO
} StandEstado;

typedef struct Stand {
    int numero;
    float ancho;
    float largo;
    StandEstado estado;
    struct Stand *siguiente;
} Stand;


float calcularArea(const Stand *stand);
const char *estadoAString(StandEstado estado);

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado);
void insertarOrdenadoPorArea(Stand **cabeza, Stand *nuevo);
Stand *buscarStand(Stand *cabeza, int numero);
int actualizarStand(Stand **cabeza, int numero, float ancho, float largo, StandEstado estado);
int borrarStand(Stand **cabeza, int numero);
void imprimirLista(const Stand *cabeza);
void liberarLista(Stand **cabeza);

#endif
