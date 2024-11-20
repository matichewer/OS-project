#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


void main(int argc, char *param[]){
	
	char dir[100];
	mode_t mode = 0777;
	
	if(param[1]==NULL) {
		printf("Falta un introducir un parametro.\n \n");
	} else {		
		strncpy(dir, param[1], sizeof(dir));
		int resultado = mkdir(dir, 0777);		
		if (resultado == 0) {
			printf("El directorio fue creado exitosamente.\n \n");
		}
		else {
			perror("Error al crear el directorio");
		}		
	}
}
