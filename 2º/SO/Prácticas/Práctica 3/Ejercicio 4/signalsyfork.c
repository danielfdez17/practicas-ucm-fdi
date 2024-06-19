#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


/*programa que temporiza la ejecución de un proceso hijo */
void sig_handler(int sig) {
    if (sig == SIGALRM) {
        printf("Se ha alcanzado el tiempo límite\n");
        kill(getpid(), SIGKILL);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <ejecutable>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Hijo
        if (execvp(argv[1], &argv[1]) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Padre
        struct sigaction sa;
        sa.sa_handler = sig_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGALRM, &sa, NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        alarm(5);
        int status;
        if (wait(&status) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("El hijo ha finalizado normalmente\n");
        } else if (WIFSIGNALED(status)) {
            printf("El hijo ha sido terminado por una señal\n");
        }
    }
    return 0;
}
