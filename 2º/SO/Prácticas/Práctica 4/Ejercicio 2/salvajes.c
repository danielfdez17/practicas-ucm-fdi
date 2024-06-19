#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define M 10
#define SHM_KEY 1234
#define SEM_KEY "/mysemaphore"

int shmid;
int semid;
int servings;

void getServingFromPot(int processId) {
    struct sembuf mutex;

    mutex.sem_num = 0;   // Indice del semaforo
    mutex.sem_op = -1;   // Se decrementa el valor del semaforo
    mutex.sem_flg = 0;   // Sin flags especiales

    // Adquirir el 'mutex'
    semop(semid, &mutex, 1);

    // Decrement the number of servings
    int* data = (int*) shmat(shmid, NULL, 0);
    *data--;

    // Liberar el 'mutex'
    mutex.sem_op = 1;   // Incrementa el valor del semáforo
    semop(semid, &mutex, 1);

    shmdt(data);

    printf("Salvaje %d: Ha cogido una ración del caldero.\n", processId);
}

void eat(int processId) {
    printf("Salvaje %d: Estoy comiendo.\n", processId);
    sleep(1);  // Simulate time to eat
    printf("Salvaje %d: He terminado de comer.\n", processId);
}

int main() {
    // Se intenta abrir la memoria compartida
    shmid = shmget(SHM_KEY, sizeof(servings), 0);
    if (shmid == -1) {
        perror("shmget");
        printf("No se ha encontrado la memoria compartida. Ejecute primero el programa cocinero.\n");
        exit(1);
    }

    // Se intenta abrir el semaforo
    semid = semget(IPC_PRIVATE, 1, 0);
    if (semid == -1) {
        perror("semget");
        printf("No se ha encontrado el semáforo. Ejecute primero el programa cocinero.\n");
        exit(1);
    }

    // Se ejecuta el 'programa'
    for (int i = 0; i < M; i++) {
        getServingFromPot(getpid());
        eat(getpid());
    }

    return 0;
}
