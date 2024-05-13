#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Tarea {
    int TareaID;
    char Descripcion[100];
    int Duracion;
};

struct Nodo {
    struct Tarea T;
    struct Nodo *Siguiente;
};

struct Nodo* agregarTarea(struct Nodo *lista, struct Tarea nuevaTarea) {
    struct Nodo *nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->T = nuevaTarea;
    nuevoNodo->Siguiente = lista;
    return nuevoNodo;
}

void marcarComoRealizada(struct Nodo **pendientes, struct Nodo **realizadas, int TareaID) {
    struct Nodo *actual = *pendientes;
    struct Nodo *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != TareaID) {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if (actual != NULL) {
        if (anterior == NULL) {
            *pendientes = actual->Siguiente;
        } else {
            anterior->Siguiente = actual->Siguiente;
        }

        actual->Siguiente = *realizadas;
        *realizadas = actual;
    }
}

void listarTareas(struct Nodo *lista, const char* titulo) {
    printf("\n%s:\n", titulo);
    struct Nodo *actual = lista;
    while (actual != NULL) {
        printf("Tarea ID: %d, Descripcion: %s, Duracion: %d\n", actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
        actual = actual->Siguiente;
    }
}

void consultarTareaPorID(struct Nodo *pendientes, struct Nodo *realizadas, int TareaID) {
    struct Nodo *actual = pendientes;
    bool encontrada = false;

    while (actual != NULL) {
        if (actual->T.TareaID == TareaID) {
            printf("\nTarea encontrada - Pendiente:\n");
            printf("Tarea ID: %d, Descripcion: %s, Duracion: %d\n", actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
            encontrada = true;
            break;
        }
        actual = actual->Siguiente;
    }

    if (!encontrada) {
        actual = realizadas;
        while (actual != NULL) {
            if (actual->T.TareaID == TareaID) {
                printf("\nTarea encontrada - Realizada:\n");
                printf("Tarea ID: %d, Descripcion: %s, Duracion: %d\n", actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
                encontrada = true;
                break;
            }
            actual = actual->Siguiente;
        }
    }

    if (!encontrada) {
        printf("\nTarea no encontrada.\n");
    }
}

int main() {
    struct Nodo *tareasPendientes = NULL;
    struct Nodo *tareasRealizadas = NULL;
    char respuesta;

    // Agregar tareas de ejemplo
    struct Tarea tarea1 = {1000, "Realizar informe", 60};
    tareasPendientes = agregarTarea(tareasPendientes, tarea1);

    struct Tarea tarea2 = {1001, "Enviar correos", 30};
    tareasPendientes = agregarTarea(tareasPendientes, tarea2);

    do {
        int TareaID;
        listarTareas(tareasPendientes, "Tareas Pendientes");

        printf("\nIngrese el ID de la tarea que desea marcar como realizada: ");
        scanf("%d", &TareaID);

        marcarComoRealizada(&tareasPendientes, &tareasRealizadas, TareaID);

        printf("\n¿Desea marcar otra tarea como realizada? (s/n): ");
        scanf(" %c", &respuesta);

    } while (respuesta == 's' || respuesta == 'S');

    listarTareas(tareasPendientes, "Tareas Pendientes");
    listarTareas(tareasRealizadas, "Tareas Realizadas");

    // Consultar tarea por ID
    int consultaID;
    printf("\nIngrese el ID de la tarea que desea consultar: ");
    scanf("%d", &consultaID);

    consultarTareaPorID(tareasPendientes, tareasRealizadas, consultaID);

    return 0;
}