#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#define COMANDOS_DIR "./bin/comandos/"

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);

    int pid;  // Variable para almacenar el PID del proceso hijo
    int ejecutando = 1;  // Variable entera para controlar el bucle (1: sigue, 0: termina)
    char opcion[100];  // Para almacenar el comando ingresado por el usuario
    char rutaCompleta[256];  // Para construir la ruta completa del comando
    char *operacion;
    char *param1;
    char *param2;
    char fin[] = " ";

    printf("Bienvenido a la Minishell: Para ver los comandos utilice 'help' \n\n");

    // Bucle principal de la shell
    while (ejecutando) {
        // Pedimos al usuario que ingrese un comando
        printf("> ");
        fgets(opcion, 100, stdin);
        opcion[strlen(opcion) - 1] = '\0';  // Quitamos el carácter '\n' al final de la entrada

        // Separar el comando y los parámetros
        operacion = strtok(opcion, fin);  // Comando
        param1 = strtok(NULL, fin);  // Primer parámetro (si existe)
        param2 = strtok(NULL, fin);  // Segundo parámetro (si existe)

        // Comprobamos si el usuario quiere salir
        if (strcmp(operacion, "exit") == 0) {
            printf("Gracias por usar la Minishell.\nAutores: Franco Popp y Matias David Schwerdt.\n");
            ejecutando = 0;  // Cambiamos la condición a 0 para salir del bucle
        } 
        else {  // Si no es "exit", ejecutamos el comando ingresado
            // Creamos un proceso hijo
            pid = fork();

            if (pid == -1) {
                perror("Error al crear el proceso hijo");
                exit(EXIT_FAILURE);
            } 
            else if (pid == 0) {  // Este es el proceso hijo
                // Construimos la ruta completa del comando
                snprintf(rutaCompleta, sizeof(rutaCompleta), "%s%s", COMANDOS_DIR, operacion);

                // Creamos los parámetros para la función execve()
                char *argv[] = {operacion, param1, param2, NULL};
                char *env[] = {NULL};

                // Intentamos ejecutar el comando en la ruta dada
                if (execve(rutaCompleta, argv, env) == -1) {
                    perror("Error al ejecutar el comando");  // Si falla, imprimimos el error
                    exit(EXIT_FAILURE);  // Finalizamos el hijo en caso de error
                }
            } 
            else {  // Este es el proceso padre
                // Esperamos que el proceso hijo termine
                waitpid(pid, NULL, 0);
            }
        }
    }

    return 0;
}
