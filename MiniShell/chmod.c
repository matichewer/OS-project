#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // Para los permisos S_IRUSR, S_IWUSR
#include <unistd.h>
#include <sys/types.h> 


int main(int argc, char *param[]) {
    
    mode_t new_permissions;
    int resultado = -1; 
    int encontre = 0;

    if (argc < 3) {
        printf("Uso: %s <archivo o directorio> <opcion>\nOpciones:\n  -le  (lectura)\n  -lees (lectura y escritura)\n  -ej  (ejecución y lectura)\n\n", param[0]);
        return 1;
    }

    struct stat path_stat;
    stat(param[1], &path_stat);

    for (int i = 0; i < 3 && !encontre; i++) {
        if (strcmp(param[2], "-le") == 0) {
            resultado = 0;
            encontre = 1;
            new_permissions = S_IRUSR;
        } else if (strcmp(param[2], "-lees") == 0) {
            resultado = 2;
            encontre = 1;
            new_permissions = S_IRUSR | S_IWUSR;
            if (S_ISDIR(path_stat.st_mode)) { // Si es un directorio, agrega el permiso de ejecución
                new_permissions |= S_IXUSR;
            }
        } else if (strcmp(param[2], "-ej") == 0) {
            resultado = 3;
            encontre = 1;
            new_permissions = S_IXUSR | S_IRUSR;
        }
    }

    if (resultado == -1) {
        printf("Opción de permisos incorrecta. Las opciones son '-le', '-ej', y '-lees'.\n\n");
        return 1;
    }

    if (chmod(param[1], new_permissions) == -1) {
        perror("Error al cambiar los permisos del archivo o directorio\n");
        return 1;
    } else {
        printf("Permisos cambiados correctamente.\n\n");
    }

    return 0;
}
