#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int n; // numero
    char p; // prioridad
} thilo;

void *thread_usuario(void *arg) {
	thilo *args = (thilo *) arg;
    int thread_id = (int) pthread_self();

    int thread_num = args->n;
    char priority = args->p;

    printf("Soy el hilo %d, mi número de hilo es %d y mi prioridad es %c\n", 
            thread_id, thread_num, priority);
    free(args);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	pthread_t threads[8];

    for (int i = 0; i < 8; i++) {
        thilo *args = malloc(sizeof(thilo));
        args->n = i;
        args->p = (i % 2 == 0) ? 'P' : 'N';

        pthread_create(&threads[i], NULL, thread_usuario, (void *) args);
    }

    for (int i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
