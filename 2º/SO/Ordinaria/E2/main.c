#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Orden a cumplir en el tablon.
int tablon;

// E2. Variables para sincronización.
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex
pthread_cond_t cond_capataz = PTHREAD_COND_INITIALIZER; // VC para el capataz
pthread_cond_t* cond_obreros; // Array de VCs para todos los obreros.

// E2. Variables globales.
int* obreros_leidos; // Array de enteros que indica si cada obrero ha leído (1) o no (-1) la orden actual.
int obreros_pendientes; // Variable para contar el número de obreros pendientes de leer la orden actual.

typedef struct {
    int id;         // Identificador del obrero.
    int nordenes;   // Numero de ordenes a leer/ejecutar.
} obrero_t;

typedef struct {
    int nobreros;   // Numero de obreros a cargo.
    int nordenes;   // Numero de ordenes a colgar.
} capataz_t;

void escribeOrden(int Norden, int Nobreros) {
    int i;

    printf("[Capataz ] Esperando para escribir nueva orden\n");

    // E2. Espera si hay obreros pendientes de leer orden
    pthread_mutex_lock(&mutex);
    while (obreros_pendientes > 0) {
        pthread_cond_wait(&cond_capataz, &mutex);
    }

    // Escribir siguiente orden en el tablon.
    tablon = Norden;

    printf("[Capataz ] Nueva orden escrita (%d)\n", tablon);

    // E2. Avisa a los obreros porque hay una nueva orden en el tablón.
    for (i = 0; i < Nobreros; i++) {
        obreros_leidos[i] = 0;
    }
    obreros_pendientes = Nobreros;
    pthread_cond_broadcast(&cond_obreros[Norden % Nobreros]);

    pthread_mutex_unlock(&mutex);
}

// Funcion de entrada para hilo capataz
void* capataz(void* arg) {
    capataz_t* capataz_info = (capataz_t*)arg; // E1. Recogida de argumentos.
    int Nobreros = capataz_info->nobreros; // E1. Número de obreros a cargo.
    int Nordenes = capataz_info->nordenes; // E1. Número de ordenes a colgar.
    int Norden = 0;

    while (Norden++ < Nordenes)
        escribeOrden(Norden, Nobreros);
}

int leeorden(int id) {
    int orden;

    printf("[Obrero %d] Esperando orden\n", id);

    // E2. Espera si el tablon esta vacio, o si lo que hay en el tablon no lo leyo ya este mismo obrero.
    pthread_mutex_lock(&mutex);
    while (tablon == -1 || obreros_leidos[id] == 1) {
        pthread_cond_wait(&cond_obreros[id], &mutex);
    }

    // Recoge la orden del tablon.
    orden = tablon;

    obreros_leidos[id] = 1;
    obreros_pendientes--;

    // E2. Informa de que ya ha leido el tablon y avisa si es necesario para que el capaz cuelgue una nueva orden.
    if (obreros_pendientes == 0) {
        pthread_cond_signal(&cond_capataz);
    }

    printf("[Obrero %d] Orden leída (%d)\n", id, orden);

    pthread_mutex_unlock(&mutex);

    return orden;
}

void trabaja(int id, int orden) {
    printf("[Obrero %d] Trabajando (%d)\n", id, orden);
    sleep(rand() % 10);
    printf("[Obrero %d] Finaliza orden (%d)\n", id, orden);
}

// Funcion de entrada para hilo obrero
void* obrero(void* arg) {
    obrero_t* obrero_info = (obrero_t*)arg; // E1. Recogida de argumentos.
    int id = obrero_info->id;               // E1. Identificador de obrero.
    int Nordenes = obrero_info->nordenes;   // E1. Número de ordenes a ejecutar.

    int Norden = 0;
    int orden;

    while (Norden++ < Nordenes) {
        orden = leeorden(id);
        trabaja(id, orden);
    }

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <Nobreros> <Nordenes>\n", argv[0]);
        return 1;
    }

    int Nobreros = atoi(argv[1]); // Primer argumento del programa.
    int Nordenes = atoi(argv[2]); // Segundo argumento del programa.
    int i;

    // E1. Creación de estructuras de datos dinámicas para argumentos de cada hilo (si es necesario).
    cond_obreros = (pthread_cond_t*)malloc(Nobreros * sizeof(pthread_cond_t));
    obreros_leidos = (int*)malloc(Nobreros * sizeof(int));
    obreros_pendientes = Nobreros;

    // Inicializar las variables condicionales para obreros
    for (i = 0; i < Nobreros; i++) {
        pthread_cond_init(&cond_obreros[i], NULL);
        obreros_leidos[i] = 0;
    }

    // E1. Creación de hilo para capataz (función capataz).
    pthread_t capataz_thread;
    capataz_t capataz_info;
    capataz_info.nobreros = Nobreros;
    capataz_info.nordenes = Nordenes;
    if (pthread_create(&capataz_thread, NULL, capataz, &capataz_info) != 0) {
        perror("Error al crear el hilo del capataz");
        return 1;
    }

    // E1. Creación de hilos para obreros (función obrero).
    pthread_t* obreros_threads = (pthread_t*)malloc(Nobreros * sizeof(pthread_t));
    obrero_t* obreros_info = (obrero_t*)malloc(Nobreros * sizeof(obrero_t));
    for (i = 0; i < Nobreros; i++) {
        obreros_info[i].id = i;
        obreros_info[i].nordenes = Nordenes;
        if (pthread_create(&obreros_threads[i], NULL, obrero, &obreros_info[i]) != 0) {
            perror("Error al crear el hilo del obrero %d", i + 1);
            return 1;
        }
    }

    // E1. Espera a la finalización de hilos.
    pthread_join(capataz_thread, NULL);
    for (i = 0; i < Nobreros; i++) {
        pthread_join(obreros_threads[i], NULL);
    }

    // E1. Liberación de estructuras de datos dinámicas (si es necesario).
    free(obreros_threads);
    free(obreros_info);
    free(cond_obreros);
    free(obreros_leidos);

    // E1. Liberación de otros recursos.

    return 0;
}
