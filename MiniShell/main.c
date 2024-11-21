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
    char ruta_completa[256];  // Para construir la ruta completa del comando
    char *comando;
    char *param1;
    char *param2;
    char fin[] = " ";

    printf("Bienvenido a la Minishell: Para ver los comandos utilice 'help' \n\n");

    while (ejecutando) {
        printf("> ");
        fgets(opcion, 100, stdin);
        opcion[strlen(opcion) - 1] = '\0';  // Quitamos el carácter '\n' al final de la entrada

        // Separar el comando y los parámetros
        comando = strtok(opcion, fin); 
        param1 = strtok(NULL, fin);
        param2 = strtok(NULL, fin);

	if ((comando != NULL) && (strlen(comando) != 0)) {

        if (strcmp(comando, "exit") == 0) {
            printf("Gracias por usar la Minishell.\nAutores: Franco Popp y Matias David Schwerdt.\n");
            ejecutando = 0;
        } 
        else { 
            pid = fork();

            if (pid == -1) {
                perror("Error al crear el proceso hijo");
                exit(1);
            } 
            else if (pid == 0) { 
                // Construimos la ruta completa del comando
                snprintf(ruta_completa, sizeof(ruta_completa), "%s%s", COMANDOS_DIR, comando);

                // Creamos los parámetros para la función execve()
                char *argv[] = {comando, param1, param2, NULL};
                char *env[] = {NULL};

                if (execve(ruta_completa, argv, env) == -1) {
                    perror("Error al ejecutar el comando");
                    exit(1);
                }
            } 
            else {
                waitpid(pid, NULL, 0);
            }
        }
	}
    }

    return 0;
}
