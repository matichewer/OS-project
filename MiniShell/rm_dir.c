#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


void main(int argc, char *param[]){
	char dir[100];

	if (param[1]==NULL) {
		printf("Falta introducir un parametro.\n\n");
	}
	else {		
		strncpy(dir, param[1], sizeof(dir));
		int resultado = rmdir(param[1]);
			
		if (resultado == 0) {
			printf("Directorio eliminado exitosamente.\n\n");
		} else {
			perror("Error al eliminar el directorio");
		}
	}
}
