#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>

#define BUFFER_SIZE 1

int main(int argc, char *argv[]) {
    int opt;
    int bytes_to_skip = 0;
    int read_from_end = 0;
    // Parsear los argumentos
    while ((opt = getopt(argc, argv, "n:e")) != -1) {
        switch (opt) {
            case 'n':
                bytes_to_skip = atoi(optarg);
                break;
            case 'e':
                read_from_end = 1;
                break;
            default:
                fprintf(stderr, "Uso: %s [-n N] [-e] fichero\n", argv[0]);
                return 1;
        }
    }
    
    if (optind >= argc) {
        fprintf(stderr, "Se requiere especificar un fichero.\n");
        fprintf(stderr, "Uso: %s [-n N] [-e] fichero\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[optind];
    
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el fichero");
        return 1;
    }
    
    off_t offset;
    if (read_from_end) {
        struct stat st;
        if (fstat(fd, &st) == -1) {
            perror("Error al obtener información del fichero");
            return 1;
        }
        offset = st.st_size - bytes_to_skip;
    } else {
        offset = bytes_to_skip;
    }
    
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("Error al posicionar el puntero de lectura");
        return 1;
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error al escribir en la salida estándar");
            return 1;
        }
    }
    
    if (bytes_read == -1) {
        perror("Error al leer el fichero");
        return 1;
    }
    
    close(fd);
    
    return 0;
}
