#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER_SIZE 512


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <fichero_origen> <fichero_destino>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (lstat(argv[1], &st) == -1) {
        perror("Error al obtener información del fichero origen");
        return 1;
    }

    if (S_ISREG(st.st_mode)) {
        // Fichero regular, realizar copia como en el ejercicio anterior
		char buffer[BUFFER_SIZE];
		ssize_t bytes_leidos, bytes_escritos;

		int fdo = open(argv[1], O_RDONLY);
		if (fdo == -1) {
			perror("Error al abrir el fichero origen");
		}
		int fdd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fdd == -1) {
			perror("Error al abrir/crear el fichero destino");
		}

		while ((bytes_leidos = read(fdo, buffer, BUFFER_SIZE)) > 0) {
			bytes_escritos = write(fdd, buffer, bytes_leidos);
			if (bytes_escritos == -1) {
				perror("Error al escribir en el fichero destino");
			}
		}

		if (bytes_leidos == -1) {
			perror("Error al leer el fichero origen");
		}
		close(fdo);
		close(fdd);

    } else if (S_ISLNK(st.st_mode)) {
        // Enlace simbólico, crear un nuevo enlace simbólico que apunte al mismo fichero
		ssize_t bufsize = st.st_size + 1;
		char *buffer = (char*)malloc(bufsize);
		ssize_t readlink_bytes = readlink(argv[1], buffer, bufsize);
		if (readlink_bytes == -1) {
			perror("Error al leer el enlace simbólico");
		}
		buffer[readlink_bytes] = '\0';

		if (symlink(buffer, argv[2]) == -1) {
			perror("Error al crear el enlace simbólico destino");
		}

		free(buffer);
    } else {
        // Otro tipo de fichero
        printf("El fichero origen no es un fichero regular ni un enlace simbólico.\n");
        return 1;
    }

    return 0;
}
