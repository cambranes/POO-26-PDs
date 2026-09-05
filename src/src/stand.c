#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de los estados del stand
typedef enum {
    DISPONIBLE,
    RESERVADO,
    VENDIDO
} EstadoStand;

// Estructura para la información del Stand y el nodo de la lista
typedef struct Stand {
    int numero;
    float ancho;
    float largo;
    EstadoStand estado;
    struct Stand* siguiente;
} Stand;

// --- FUNCIONES AUXILIARES ---

// Calcula el área del stand (ancho x largo)
float calcularArea(const Stand* stand) {
    if (stand == NULL) return 0.0f;
    return stand->ancho * stand->largo;
}

// Convierte el enum de EstadoStand a una cadena legible
const char* estadoAString(EstadoStand estado) {
    switch (estado) {
        case DISPONIBLE: return "Disponible";
        case RESERVADO:  return "Reservado";
        case VENDIDO:    return "Vendido";
        default:         return "Desconocido";
    }
}

// Crea e inicializa dinámicamente un nuevo nodo Stand
Stand* crearStand(int numero, float ancho, float largo, EstadoStand estado) {
    Stand* nuevo = (Stand*)malloc(sizeof(Stand));
    if (nuevo == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el stand %d.\n", numero);
        return NULL;
    }
    
    nuevo->numero = numero;
    nuevo->ancho = ancho;
    nuevo->largo = largo;
    nuevo->estado = estado;
    nuevo->siguiente = NULL;
    
    return nuevo;
}

// --- OPERACIONES DE LA LISTA ---

// Inserta un nodo de forma ordenada según el área (de menor a mayor)
void insertarOrdenadoPorArea(Stand** cabeza, Stand* nuevoNodo) {
    if (nuevoNodo == NULL || cabeza == NULL) return;

    float areaNuevo = calcularArea(nuevoNodo);

    // Caso 1: La lista está vacía o el nuevo nodo tiene un área menor que la cabeza
    if (*cabeza == NULL || calcularArea(*cabeza) >= areaNuevo) {
        nuevoNodo->siguiente = *cabeza;
        *cabeza = nuevoNodo;
        return;
    }

    // Caso 2: Insertar en medio o al final de la lista
    Stand* actual = *cabeza;
    while (actual->siguiente != NULL && calcularArea(actual->siguiente) < areaNuevo) {
        actual = actual->siguiente;
    }

    nuevoNodo->siguiente = actual->siguiente;
    actual->siguiente = nuevoNodo;
}

// Busca un stand por su número identificador
Stand* buscarStand(Stand* cabeza, int numero) {
    Stand* actual = cabeza;
    while (actual != NULL) {
        if (actual->numero == numero) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// Borra un nodo según su número identificador y libera su memoria.
// Retorna 1 si se eliminó con éxito, 0 si la lista está vacía o el elemento no fue encontrado.
int borrarStand(Stand** cabeza, int numero) {
    if (cabeza == NULL || *cabeza == NULL) return 0;

    Stand* actual = *cabeza;
    Stand* previo = NULL;

    // Verificar si el nodo a eliminar es la cabeza
    if (actual != NULL && actual->numero == numero) {
        *cabeza = actual->siguiente;
        free(actual);
        return 1;
    }

    // Buscar el nodo a eliminar manteniendo referencia del previo
    while (actual != NULL && actual->numero != numero) {
        previo = actual;
        actual = actual->siguiente;
    }

    // Si no se encontró el número en la lista
    if (actual == NULL) return 0;

    // Desvincular y liberar memoria
    previo->siguiente = actual->siguiente;
    free(actual);
    return 1;
}

// Actualiza las dimensiones o estado de un stand reordenándolo en la lista
void actualizarStand(Stand** cabeza, int numero, float nuevoAncho, float nuevoLargo, EstadoStand nuevoEstado) {
    if (cabeza == NULL || *cabeza == NULL) return;

    Stand* objetivo = buscarStand(*cabeza, numero);
    if (objetivo == NULL) {
        printf("Stand %d no encontrado para actualizacion.\n", numero);
        return;
    }

    // Si el área no cambia, se actualizan los datos sin reestructurar la lista
    float areaVieja = calcularArea(objetivo);
    float areaNueva = nuevoAncho * nuevoLargo;

    if (areaVieja == areaNueva) {
        objetivo->ancho = nuevoAncho;
        objetivo->largo = nuevoLargo;
        objetivo->estado = nuevoEstado;
    } else {
        // Si el área cambia, se remueve de la lista y se vuelve a insertar ordenadamente
        borrarStand(cabeza, numero);
        Stand* actualizado = crearStand(numero, nuevoAncho, nuevoLargo, nuevoEstado);
        if (actualizado != NULL) {
            insertarOrdenadoPorArea(cabeza, actualizado);
        }
    }
}

// Imprime los elementos de la lista
void imprimirLista(const Stand* cabeza) {
    const Stand* actual = cabeza;
    printf("\n--- LISTA DE STANDS FILEY (Ordenados por Area) ---\n");
    if (actual == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    while (actual != NULL) {
        printf("ID: %-4d | Dimensiones: %5.2fm x %5.2fm | Area: %6.2fm2 | Estado: %s\n",
               actual->numero, actual->ancho, actual->largo,
               calcularArea(actual), estadoAString(actual->estado));
        actual = actual->siguiente;
    }
    printf("--------------------------------------------------\n");
}

// Libera toda la memoria asignada dinámicamente en la lista
void liberarLista(Stand** cabeza) {
    if (cabeza == NULL) return;

    Stand* actual = *cabeza;
    Stand* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    *cabeza = NULL;
}

// --- FUNCIÓN MAIN DE PRUEBA ---

int main() {
    Stand* listaStands = NULL;

    // 1. Inserción de prueba
    printf("Insertando stands...\n");
    insertarOrdenadoPorArea(&listaStands, crearStand(101, 3.0f, 3.0f, DISPONIBLE)); // Área: 9
    insertarOrdenadoPorArea(&listaStands, crearStand(102, 2.0f, 2.0f, RESERVADO));  // Área: 4
    insertarOrdenadoPorArea(&listaStands, crearStand(103, 4.0f, 5.0f, VENDIDO));    // Área: 20
    insertarOrdenadoPorArea(&listaStands, crearStand(104, 2.5f, 3.0f, DISPONIBLE)); // Área: 7.5

    imprimirLista(listaStands);

    // 2. Búsqueda de prueba
    int idBuscar = 101;
    Stand* encontrado = buscarStand(listaStands, idBuscar);
    if (encontrado) {
        printf("\nStand %d encontrado. Estado actual: %s\n", idBuscar, estadoAString(encontrado->estado));
    }

    // 3. Actualización (Cambio de área que requiere reordenamiento)
    printf("\nActualizando Stand 102 (incremento de tamano a 6x5 = 30m2)...");
    actualizarStand(&listaStands, 102, 6.0f, 5.0f, VENDIDO);
    imprimirLista(listaStands);

    // 4. Eliminación de un nodo
    printf("\nBorrando Stand 104...");
    if (borrarStand(&listaStands, 104)) {
        printf(" Eliminado exitosamente.\n");
    } else {
        printf(" No se pudo eliminar.\n");
    }
    imprimirLista(listaStands);

    // 5. Liberar la memoria completa
    printf("\nLiberando toda la memoria de la lista...");
    liberarLista(&listaStands);
    imprimirLista(listaStands);

    return 0;
} 