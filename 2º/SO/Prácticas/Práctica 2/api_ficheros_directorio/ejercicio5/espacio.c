#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void calculateSize(const char *path, long long *totalSize) {
    struct stat st;
    if (lstat(path, &st) == -1) {
        perror("Error al obtener información del fichero");
        return;
    }

    if (S_ISREG(st.st_mode)) {
        *totalSize += (st.st_blocks * 512) / 1024; // Convertir a kilobytes
    } else if (S_ISDIR(st.st_mode)) {
        DIR *dir = opendir(path);
        if (dir == NULL) {
            perror("Error al abrir el directorio");
            return;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char newPath[1024];
                snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
                calculateSize(newPath, totalSize);
            }
        }

        closedir(dir);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s fichero1 fichero2 ...\n", argv[0]);
        return 1;
    }

    long long totalSize = 0;
    for (int i = 1; i < argc; i++) {
        calculateSize(argv[i], &totalSize);
        printf("%lldK %s\n", totalSize, argv[i]);
        totalSize = 0;
    }

    return 0;
}
