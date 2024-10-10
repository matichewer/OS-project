#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#define COMANDOS_DIR "./bin/comandos/"

// Función para buscar un comando en la carpeta "comandos"
int buscarComando(const char *comando, char *rutaCompleta) {
    DIR *dir;
    struct dirent *entry;

    // Abrimos la carpeta "comandos"
    dir = opendir(COMANDOS_DIR);
    if (dir == NULL) {
        perror("No se puede abrir el directorio de comandos");
        return -1;
    }

    // Leemos los archivos en el directorio
    while ((entry = readdir(dir)) != NULL) {
        // Ignoramos las entradas "." y ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Comparamos el nombre del archivo con el comando ingresado
        if (strcmp(entry->d_name, comando) == 0) {
            // Si encontramos el comando, construimos la ruta completa
            snprintf(rutaCompleta, 256, "%s%s", COMANDOS_DIR, entry->d_name);
            closedir(dir);
            return 0;  // Comando encontrado
        }
    }

    closedir(dir);
    return -1;  // Comando no encontrado
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);

    // Declaración de variable pid para guardar el resultado de fork()
    int pid;

    // Declaración de cadenas de texto utilizadas
    char opcion[100];
    char *operacion;
    char *param1;
    char *param2;

    char fin[] = " ";
    char rutaCompleta[256];  // Para almacenar la ruta completa del comando encontrado

    printf("\nBienvenido a la Minishell: Para ver los comandos utilice '-help' \n\n");

    do {
        // Pedimos al usuario que ingrese un comando
        fgets(opcion, 100, stdin);
        opcion[strlen(opcion) - 1] = '\0'; // Quitamos el carácter '\n'

        operacion = strtok(opcion, fin); // Se pasa el comando a operacion
        param1 = strtok(NULL, fin);      // Primer parámetro
        param2 = strtok(NULL, fin);      // Segundo parámetro

        if (strcmp(operacion, "-exit") == 0) {  // Función "-exit" de salida
            printf("Gracias por usar la Minishell.\nAutores: Franco Popp y Matias David Schwerdt.\n");
            exit(0);
        }

        // Buscamos si el comando ingresado existe en la carpeta "comandos"
        if (buscarComando(operacion, rutaCompleta) == -1) {
            printf("La operacion %s no es valida o no existe en la carpeta de comandos.\n", operacion);
            continue;  // Volvemos al inicio del loop
        }

        // Si el comando es válido, creamos un proceso hijo para ejecutarlo
        pid = fork();
        if (pid == -1) {
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        }
        
        if (pid != 0) {
            waitpid(pid, NULL, 0);  // El padre espera al hijo
        }

    } while (pid != 0);  // El hijo sale del while

    // Creamos los parámetros para la función execve()
    char *argv[] = {operacion, param1, param2, NULL};
    char *env[] = {NULL};

    // Ejecutamos el comando encontrado
    if (execve(rutaCompleta, argv, env) == -1) {
        perror("execve");  // Manejo de errores si execve falla
    }

    exit(0);
}
