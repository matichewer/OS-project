#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX 1000

void main(int argc, char *param[]) {
    char dir[100];
    
    if (param[1] == NULL) {
        printf("Falta un introducir un parametro.\n\n");
        return;
    }

    strncpy(dir, param[1], sizeof(dir) - 1);
    dir[sizeof(dir) - 1] = '\0'; // Asegurar terminación nula

    struct stat fileStat;
    if (stat(dir, &fileStat) != 0) {
        perror("Error: el archivo no existe");
        return;
    }

    if (S_ISDIR(fileStat.st_mode)) {
        printf("Error: El parámetro corresponde a un directorio, no un archivo.\n\n");
        return;
    }

    FILE *f = fopen(dir, "r");
    if (f == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char leido[MAX];
    while (fgets(leido, MAX, f) != NULL) {
        printf("%s", leido);
    }

    fclose(f);
}
