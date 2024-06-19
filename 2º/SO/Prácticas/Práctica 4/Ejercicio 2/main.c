#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define M 5

int main() {
    // Crear proceso para el cocinero
    pid_t cocinero_pid = fork();
    if (cocinero_pid == -1) {
        perror("Error al crear el proceso del cocinero");
        exit(1);
    } else if (cocinero_pid == 0) {
        // Proceso hijo (cocinero)
        execl("./cocinero", "cocinero", NULL);
        perror("Error al ejecutar el programa cocinero");
        exit(1);
    }

    // Esperar a que el cocinero termine
    wait(NULL);

    // Crear procesos para los salvajes
    for (int i = 0; i < M; i++) {
        pid_t salvaje_pid = fork();
        if (salvaje_pid == -1) {
            perror("Error al crear el proceso del salvaje");
            exit(1);
        } else if (salvaje_pid == 0) {
            // Proceso hijo (salvaje)
            execl("./salvaje", "salvaje", NULL);
            perror("Error al ejecutar el programa salvaje");
            exit(1);
        }
    }

    // Esperar a que todos los salvajes terminen
    for (int i = 0; i < M; i++) {
        wait(NULL);
    }

    return 0;
}
