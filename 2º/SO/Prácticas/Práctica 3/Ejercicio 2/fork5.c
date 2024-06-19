#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* programa que crea N hijos siguiendo un grado de dependencias. Usa las
 * versiones de execl y execlp */
 
void proceso(int i) {
 	if (i % 2 == 0) { // par
 		execl("/bin/echo", "echo", NULL);
 	}
 	else { // impar
 		execlp("/bin/echo", "echo", NULL);
 	}
}

void crear_hijo(int i) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        proceso(i);
        exit(EXIT_SUCCESS);
    } else {
        printf("Proceso P%d creado con PID %d\n", i, pid);
    }
}

int main(int argc, char **argv) {

	// P0 -> P1
	crear_hijo(1);
    wait(NULL);
	// P1 -> P2, P5, P7
    crear_hijo(2);
    crear_hijo(5);
    crear_hijo(7);
    wait(NULL);
	// P2 -> P3, P4
    crear_hijo(3);
    crear_hijo(4);
    wait(NULL);
	// P3 -> P8
	// P4 -> P6
	// P5 -> P6
	crear_hijo(6);
    wait(NULL);
	// P6 -> P8
	// P7 -> P8
	crear_hijo(8);
    wait(NULL);
	// P8 
/* 	pid_t pid1, pid2, pid3, pid4, pid5, pid6, pid7, pid8;
    // P1
    pid1 = fork();
    if (pid1 == 0) { // proceso hijo
        execlp("echo", "echo", "P0", NULL);
        exit(EXIT_SUCCESS);
    } else { // proceso padre
        waitpid(pid1, NULL, 0);
        // P2, P5 Y P7
        pid2 = fork();
        if (pid2 == 0) { // proceso hijo
            execlp("echo", "echo", "P1", NULL);
            exit(EXIT_SUCCESS);
        } else { // proceso padre
            pid5 = fork();
            if (pid5 == 0) { // proceso hijo
                execlp("echo", "echo", "P4", NULL);
                exit(EXIT_SUCCESS);
            } else { // proceso padre
                pid7 = fork();
                if (pid7 == 0) { // proceso hijo
                    execlp("echo", "echo", "P6", NULL);
                    exit(EXIT_SUCCESS);
                } else { // proceso padre
                    waitpid(pid2, NULL, 0);
                    waitpid(pid5, NULL, 0);
                    waitpid(pid7, NULL, 0);
                    // P3 Y P4
                    pid3 = fork();
                    if (pid3 == 0) { // proceso hijo
                        execlp("echo", "echo", "P2", NULL);
                        exit(EXIT_SUCCESS);
                    } else { // proceso padre
                        pid4 = fork();
                        if (pid4 == 0) { // proceso hijo
                            execlp("echo", "echo", "P3", NULL);
                            exit(EXIT_SUCCESS);
                        } else { // proceso padre
                            waitpid(pid3, NULL, 0);
                            waitpid(pid4, NULL, 0);
                            // P6
                            pid6 = fork();
                            if (pid6 == 0) { // proceso hijo
                                execlp("echo", "echo", "P5", NULL);
                                exit(EXIT_SUCCESS);
                            } else { // proceso padre
                                waitpid(pid6, NULL, 0);
                                // P3, P6 Y P7
                                pid8 = fork();
                                if (pid8 == 0) { // proceso hijo
                                    execlp("echo", "echo", "P7", NULL);
                                    exit(EXIT_SUCCESS);
                                } else { // proceso padre
                                    waitpid(pid3, NULL, 0);
                                    waitpid(pid6, NULL, 0);
                                    waitpid(pid7, NULL, 0);
								}
							}
						}
					}
				}
			}
		}
	}
	 // proceso padre
	//wait(); // p1
	// crear 2, 5, 7
	//wait(); // p2
	// crear 3, 4
	//wait(); // p4 y p5
	// crear 6
	//wait(); // p3, p6, p7
	// crear p8
	
*/
	return 0;
}
