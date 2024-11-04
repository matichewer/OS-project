#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *param[]) {
    struct stat file_stat;
    mode_t new_permissions;
    int parametro_correcto = 1;

    if (argc != 3) {
        printf("Uso: %s <archivo o directorio> <+r | -r | +w | -w | +x | -x>\n", param[0]);
        return 1;
    }

    // Obtener los permisos actuales
    if (stat(param[1], &file_stat) == -1) {
        perror("Error al obtener los permisos actuales");
        return 1;
    }
    new_permissions = file_stat.st_mode;

    if (strcmp(param[2], "+r") == 0)
        new_permissions |= S_IRUSR;
    else if (strcmp(param[2], "-r") == 0)
        new_permissions &= ~S_IRUSR;
    else if (strcmp(param[2], "+w") == 0)
        new_permissions |= S_IWUSR;
    else if (strcmp(param[2], "-w") == 0)
        new_permissions &= ~S_IWUSR;
    else if (strcmp(param[2], "+x") == 0)
        new_permissions |= S_IXUSR;
    else if (strcmp(param[2], "-x") == 0)
        new_permissions &= ~S_IXUSR;
    else
        parametro_correcto = 0;

    if (!parametro_correcto) {
        printf("Opción de permisos incorrecta. Las opciones son '+r', '-r', '+w', '-w', '+x', y '-x'.\n\n");
        return 1;
    }

    if (chmod(param[1], new_permissions) == -1) {
        perror("Error al cambiar los permisos del archivo o directorio");
        return 1;
    } else {
        printf("Permisos cambiados correctamente.\n\n");
    }

    return 0;
}
