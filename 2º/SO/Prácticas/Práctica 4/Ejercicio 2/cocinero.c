#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>

#define M 10
#define NUMSERVINGS 5
#define SHM_KEY 1234
#define SEM_KEY "/mysemaphore"

int shmid;
int semid;
int servings;

void putServingsInPot() {
    struct sembuf mutex;

    mutex.sem_num = 0;   // Indice del semaforo
    mutex.sem_op = -1;   // Se decrementa el valor del semaforo
    mutex.sem_flg = 0;   // Sin flags especiales

    printf("Cocinero: Reponiendo el caldero...\n");
    sleep(1); 

    // Adquirir el 'mutex'
    semop(semid, &mutex, 1);

    // Incrementa el numero de servicios
    int* data = (int*) shmat(shmid, NULL, 0);
    *data = NUMSERVINGS;

    // Liberar el 'mutex'
    mutex.sem_op = 1;   // Incrementa el valor del semáforo
    semop(semid, &mutex, 1);

    shmdt(data);

    printf("Cocinero: Se han repuesto las %d raciones en el caldero.\n", NUMSERVINGS);
}

void handler(int signo) {
    if (signo == SIGTERM || signo == SIGINT) {
        // Desenlazar y liberar la memoria compartida
        shmdt(NULL);
        shmctl(shmid, IPC_RMID, NULL);

        // Liberar semaforo
        semctl(semid, 0, IPC_RMID);

        exit(0);
    }
}

int main() {
    // Crear memoria compartida
    shmid = shmget(SHM_KEY, sizeof(servings), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Enlazar la memoria compartida
    int* data = (int*) shmat(shmid, NULL, 0);
    *data = NUMSERVINGS;

    // Creacion del semaforo
    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Inicializacion del semaforo
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    // Poner los manejadores de señales
    signal(SIGTERM, handler);
    signal(SIGINT, handler);

    // Ejecutar el 'programa'
    while (1) {
        putServingsInPot();
    }

    return 0;
}
