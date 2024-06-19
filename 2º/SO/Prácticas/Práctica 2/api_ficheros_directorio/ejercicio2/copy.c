#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 512

void copy(int fdo, int fdd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_leidos, bytes_escritos;

    while ((bytes_leidos = read(fdo, buffer, BUFFER_SIZE)) > 0) {
        bytes_escritos = write(fdd, buffer, bytes_leidos);
        if (bytes_escritos == -1) {
            perror("Error al escribir en el fichero destino");
        }
    }

    if (bytes_leidos == -1) {
        perror("Error al leer el fichero origen");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <fichero_origen> <fichero_destino>\n", argv[0]);
        return 1;
    }

    int fdo = open(argv[1], O_RDONLY);
    if (fdo == -1) {
        perror("Error al abrir el fichero origen");
        return 1;
    }

    int fdd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fdd == -1) {
        perror("Error al abrir/crear el fichero destino");
        return 1;
    }

	copy(fdo, fdd);


    close(fdo);
    close(fdd);

    return 0;
}