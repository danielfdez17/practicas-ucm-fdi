#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*programa que crea dos hijos: uno no cambia de ejecutable y otro si */

int main(int argc, char *argv[]) {
    pid_t pid1, pid2;
	// Proceso padre
    printf("Soy el proceso padre con pid %d y mi padre es %d.\n", getpid(), getppid());
	// PRIMERA LLAMADA
    pid1 = fork();
	// Se la llamada no ha sido correcta se lanza un mensaje de error
    if (pid1 == -1) {
        perror("Error en la primera llamada a fork.");
        exit(EXIT_FAILURE);
    } 
    // Si la llamada ha tenido exito
    else if (pid1 == 0) { // PRIMER PROCESO HIJO
        printf("Soy el primer hijo con pid %d y mi padre es %d.\n", getpid(),getppid());
		// SEGUNDA LLAMADA
        pid2 = fork();
		// Si la llamada no ha sido correcta se lanza un error
        if (pid2 == -1) {
            perror("Error en la segunda llamada a fork.");
            exit(EXIT_FAILURE);
        }
        // Si la llamada ha tenido exito
        else if (pid2 == 0) { // SEGUNDO PROCESO HIJO
            printf("Soy el segundo hijo con pid %d y mi padre es %d.\n", getpid(), getppid());
            char *args[] = {argv[1], argv[2], NULL};
            // execvp(const char *file, char *const argv[])
            if (execvp(args[0], args) == -1) {
                perror("Error en la llamada a execvp.");
                exit(EXIT_FAILURE);
            }

        } else { // PRIMER PROCESO HIJO
            printf("Soy el primer hijo con pid %d y mi padre es %d.\n", getpid(), getppid());
            // waitpid(pid_t pid, int* wstatus, int options)
            waitpid(pid2, NULL, 0); // Se espera a que el seguno hijo termine
            exit(EXIT_SUCCESS);
        }

    } else { // PROCESO PADRE
        printf("Soy el proceso padre con pid %d y mi padre es %d.\n", getpid(), getppid());
        waitpid(pid1, NULL, 0); // Se espera a que el primer hijo termine
        exit(EXIT_SUCCESS);
    }

    return 0;
}
