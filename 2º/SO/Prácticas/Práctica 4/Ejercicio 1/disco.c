#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t vcVips = PTHREAD_COND_INITIALIZER;
pthread_cond_t vcNormales = PTHREAD_COND_INITIALIZER;

int aforo_actual = 0;
int aforo_maximo; // Max aforo (<= CAPACITY)
int *clientes; // Se guardan los clientes del archivo en el heap
int num_clientes; // Número de clientes leído del archivo


void enter_vip_client(int id) {
    pthread_mutex_lock(&mutex);
    // Esperar mientras la disco esta llena
    while (aforo_actual >= aforo_maximo) {
        printf("Cliente VIP %d esperando a que haya espacio disponible\n", id);
        pthread_cond_wait(&vcNormales, &mutex);
    }
    aforo_actual++; // Entra cuando hay espacio
    printf("Cliente VIP %d ha entrado a la discoteca\n", id);
    pthread_mutex_unlock(&mutex);
}

void enter_normal_client(int id) {
    pthread_mutex_lock(&mutex);
    // Esperar mientras no hay hueco o no hay nadie
    while (aforo_actual >= aforo_maximo || aforo_actual > 0) {
        printf("Cliente normal %d esperando a que haya espacio y no haya VIPs esperando\n", id);
        pthread_cond_wait(&vcNormales, &mutex);
    }
    // Entra cuando hay espacio
    aforo_actual++;
    printf("Cliente normal %d ha entrado a la discoteca\n", id);
    pthread_mutex_unlock(&mutex);
}

void exit_client(int id) {
    pthread_mutex_lock(&mutex);
    aforo_actual--;
    printf("Cliente %d ha salido de la discoteca\n", id);
    if (aforo_actual < aforo_maximo) {
        pthread_cond_signal(&vcNormales);
        pthread_cond_signal(&vcVips);
    }
    pthread_mutex_unlock(&mutex);
}

void dance(int id, int isvip) {
    printf("Cliente %2d (%s) bailando en la disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}

void *client(void *arg) {
    int id = *((int*)arg);
    int isvip = clientes[id];
    free(arg);
    if (isvip)
        enter_vip_client(id);
    else
        enter_normal_client(id);
    dance(id, isvip);
    exit_client(id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nombre_archivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *nombre_archivo = argv[1];
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombre_archivo);
        exit(EXIT_FAILURE);
    }

    fscanf(archivo, "%d", &num_clientes);
    if (num_clientes <= 0 || num_clientes > CAPACITY) {
        printf("Número de clientes inválido\n");
        fclose(archivo);
        return 1;
    }

    clientes = malloc(num_clientes * sizeof(int));
    if (clientes == NULL) {
        printf("Error de memoria\n");
        fclose(archivo);
        return 1;
    }

    for (int i = 0; i < num_clientes; i++) {
        int tipo_cliente;
        if (fscanf(archivo, "%d", &tipo_cliente) != 1 || (tipo_cliente != 0 && tipo_cliente != 1)) {
            printf("Formato de archivo inválido\n");
            fclose(archivo);
            free(clientes);
            return 1;
        }
        clientes[i] = tipo_cliente;
    }

    fclose(archivo);

    aforo_maximo = num_clientes;

    pthread_t *hilos = malloc(num_clientes * sizeof(pthread_t));
    if (hilos == NULL) {
        printf("Error de memoria\n");
        free(clientes);
        return 1;
    }
    // Creacion de los hilos
    for (int i = 0; i < num_clientes; i++) {
        int *arg = malloc(sizeof(int));
        if (arg == NULL) {
            printf("Error de memoria\n");
            free(clientes);
            free(hilos);
            return 1;
        }
        *arg = i;
        if (pthread_create(&hilos[i], NULL, client, arg) != 0) {
            printf("Error al crear los hilos\n");
            free(clientes);
            free(hilos);
            return 1;
        }
    }
    // Esperar a que terminen los hilos
    for (int i = 0; i < num_clientes; i++) {
        pthread_join(hilos[i], NULL);
    }
    // Liberar todos los recursos
    free(clientes);
    free(hilos);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&vcVips);
    pthread_cond_destroy(&vcNormales);

    return 0;
}
