#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* loadstr(FILE* students) {
    char buffer[1024];
    int i = 0;
    char c;
    while ((c = fgetc(students)) != '\0') {
        buffer[i++] = c;
    }
    buffer[i] = '\0';

    return strdup(buffer);
}

student_t* parse_records(char* records[], int* nr_records) {
    student_t* entries = malloc(sizeof(student_t) * (*nr_records));
    if (entries == NULL) {
        perror("Error al reservar memoria");
        return NULL;
    }

    for (int i = 0; i < *nr_records; i++) {
        char* token = strtok(records[i], ":");
        entries[i].student_id = atoi(token);

        token = strtok(NULL, ":");
        strncpy(entries[i].NIF, token, MAX_CHARS_NIF);
        entries[i].NIF[MAX_CHARS_NIF] = '\0';

        token = strtok(NULL, ":");
        entries[i].first_name = strdup(token);

        token = strtok(NULL, ":");
        entries[i].last_name = strdup(token);
    }

    return entries;
}

int dump_entries(student_t* entries, int nr_entries, FILE* students) {
    for (int i = 0; i < nr_entries; i++) {
        fwrite(&entries[i].student_id, sizeof(int), 1, students);
        fwrite(entries[i].NIF, sizeof(char), MAX_CHARS_NIF + 1, students);
        fwrite(entries[i].first_name, sizeof(char), strlen(entries[i].first_name) + 1, students);
        fwrite(entries[i].last_name, sizeof(char), strlen(entries[i].last_name) + 1, students);
    }

    return 0;
}

student_t* read_student_file(FILE* students, int* nr_entries) {
    fread(nr_entries, sizeof(int), 1, students);

    student_t* entries = malloc(sizeof(student_t) * (*nr_entries));
    if (entries == NULL) {
        perror("Error al reservar memoria");
        return NULL;
    }

    for (int i = 0; i < *nr_entries; i++) {
        fread(&entries[i].student_id, sizeof(int), 1, students);

        fread(entries[i].NIF, sizeof(char), MAX_CHARS_NIF + 1, students);

        entries[i].first_name = loadstr(students);
        entries[i].last_name = loadstr(students);
    }

    return entries;
}


void print_entry(student_t* entry, int index) {
    printf("[Entry #%d]\n", index);
    printf("\tstudent_id=%d\n", entry->student_id);
    printf("\tNIF=%s\n", entry->NIF);
    printf("\tfirst_name=%s\n", entry->first_name);
    printf("\tlast_name=%s\n", entry->last_name);
}

void list_entries(student_t* entries, int nr_entries) {
    for (int i = 0; i < nr_entries; i++) {
        print_entry(&entries[i], i);
    }
}

student_t* search_entry_by_id(student_t* entries, int nr_entries, int student_id) {
    for (int i = 0; i < nr_entries; i++) {
        if (entries[i].student_id == student_id) {
            return &entries[i];
        }
    }
    return NULL;
}

student_t* search_entry_by_nif(student_t* entries, int nr_entries, const char* NIF) {
    for (int i = 0; i < nr_entries; i++) {
        if (strcmp(entries[i].NIF, NIF) == 0) {
            return &entries[i];
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    char* file_name = NULL;
    char** records = NULL;
    int nr_records = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                file_name = argv[i + 1];
                i++;
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            // Crear fichero de registros
            if (i + 1 < argc) {
                records = &argv[i + 1];
                nr_records = argc - i - 1;
                break;
            }
        }
    }

    if (file_name == NULL) {
        fprintf(stderr, "Debe especificar un nombre de archivo con la opción -f\n");
        return 1;
    }

    if (records != NULL) {
        // Crear registros de estudiantes
        student_t* entries = parse_records(records, &nr_records);
        if (entries == NULL) {
            fprintf(stderr, "Error al analizar los registros de estudiantes\n");
            return 1;
        }

        FILE* students = fopen(file_name, "wb");
        if (students == NULL) {
            perror("Error al abrir el archivo");
            free(entries);
            return 1;
        }

        fwrite(&nr_records, sizeof(int), 1, students);
        dump_entries(entries, nr_records, students);

        fclose(students);
        free(entries);

        printf("%d records written successfully\n", nr_records);
    } else {
        // Otras operaciones (listar, añadir, buscar)
        FILE* students = fopen(file_name, "rb");
        if (students == NULL) {
            perror("Error al abrir el archivo");
            return 1;
        }

        int num_records;
        fread(&num_records, sizeof(int), 1, students);

        student_t* entries = read_student_file(students, &num_records);
        if (entries == NULL) {
            fprintf(stderr, "Error al leer los registros de estudiantes\n");
            fclose(students);
            return 1;
        }

        // Realizar las operaciones solicitadas según las opciones -l, -a, -q, etc.
        if (argc >= 3) {
            if (strcmp(argv[2], "-l") == 0) {
                list_entries(entries, num_records);
            } else if (strcmp(argv[2], "-a") == 0) {
                if (argc >= 4) {
                    int extra_records = argc - 3;
                    student_t* new_entries = parse_records(&argv[3], &extra_records);
                    if (new_entries == NULL) {
                        fprintf(stderr, "Error al analizar los registros de estudiantes adicionales\n");
                        fclose(students);
                        free(entries);
                        return 1;
                    }

                    FILE* students = fopen(file_name, "ab");
                    if (students == NULL) {
                        perror("Error al abrir el archivo");
                        free(entries);
                        free(new_entries);
                        return 1;
                    }

                    fwrite(&extra_records, sizeof(int), 1, students);
                    dump_entries(new_entries, extra_records, students);

                    fclose(students);
                    free(new_entries);

                    printf("%d extra records written successfully\n", extra_records);
                } else {
                    fprintf(stderr, "Debe especificar al menos un registro adicional con la opción -a\n");
                }
            } else if (strcmp(argv[2], "-q") == 0) {
                if (argc >= 4) {
                    if (strcmp(argv[3], "-i") == 0) {
                        if (argc >= 5) {
                            int student_id = atoi(argv[4]);
                            student_t* entry = search_entry_by_id(entries, num_records, student_id);
                            if (entry != NULL) {
                                print_entry(entry, -1);
                            } else {
                                printf("No entry was found\n");
                            }
                        } else {
                            fprintf(stderr, "Debe especificar un ID de estudiante con la opción -i\n");
                        }
                    } else if (strcmp(argv[3], "-n") == 0) {
                        if (argc >= 5) {
                            const char* NIF = argv[4];
                            student_t* entry = search_entry_by_nif(entries, num_records, NIF);
                            if (entry != NULL) {
                                print_entry(entry, -1);
                            } else {
                                printf("No entry was found\n");
                            }
                        } else {
                            fprintf(stderr, "Debe especificar un NIF con la opción -n\n");
                        }
                    } else {
                        fprintf(stderr, "Opción no reconocida: %s\n", argv[3]);
                    }
                } else {
                    fprintf(stderr, "Debe especificar una opción válida con -q\n");
                }
            } else {
                fprintf(stderr, "Opción no reconocida: %s\n", argv[2]);
            }
        }

        fclose(students);
        free(entries);
    }

    return 0;
}
