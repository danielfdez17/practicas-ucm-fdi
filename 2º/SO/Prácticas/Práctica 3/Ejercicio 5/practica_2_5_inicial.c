#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <semaphore.h>

#define N_PROCESSES 10
#define SEM_NAME "/output_sem"

int main(void) {
    int fd1, i;
    sem_t *sem;
    char buffer[6];

    // Create or open the output file
    fd1 = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd1 < 0) {
        perror("open");
        exit(1);
    }

    // Initialize semaphore
    sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Write initial zeros
    write(fd1, "00000", 5);

    // Fork child processes to write numbers
    for (i = 0; i < N_PROCESSES; i++) {
        if (fork() == 0) {
            // Child process
            sprintf(buffer, "%d", i * 11111);

            sem_wait(sem); // Acquire semaphore

            // Move file pointer to correct position
            if (lseek(fd1, i * 5, SEEK_SET) < 0) {
                perror("lseek");
                exit(1);
            }

            // Write number
            if (write(fd1, buffer, 5) < 0) {
                perror("write");
                exit(1);
            }

            sem_post(sem); // Release semaphore

            close(fd1);
            sem_close(sem);
            exit(0);
        }
    }

    // Wait for child processes to finish
    while (wait(NULL) > 0);

    // Print file contents
    lseek(fd1, 0, SEEK_SET);
    printf("File contents are:\n");
    char c;
    while (read(fd1, &c, 1) > 0)
        printf("%c", (char) c);
    printf("\n");

    // Clean up resources
    close(fd1);
    sem_close(sem);
    sem_unlink(SEM_NAME);

    exit(0);
}

/*
    int fd1, fd2, i, pos;
    char c;
    char buffer[6];
    sem_t *sem;

    fd1 = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
    write(fd1, "00000", 5);
    for (i=1; i < 10; i++) {
        pos = lseek(fd1, 0, SEEK_CUR);
        if (fork() == 0) {
            // Child 
            sprintf(buffer, "%d", i*11111);
            lseek(fd1, pos, SEEK_SET);
            write(fd1, buffer, 5);
            close(fd1);
            exit(0);
        } else {
            // Parent 
            lseek(fd1, 5, SEEK_CUR);
        }
    }

	//wait for all childs to finish
    while (wait(NULL) != -1);

    lseek(fd1, 0, SEEK_SET);
    printf("File contents are:\n");
    while (read(fd1, &c, 1) > 0)
        printf("%c", (char) c);
    printf("\n");
    close(fd1);
    exit(0);
    */
