#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>


void main(int argc, char *param[]){
	
	mode_t mode = 0777;
	
	if(param[1]==NULL) {
		printf("Falta un introducir un parametro.\n \n");
	} else {		
		int resultado = syscall(SYS_mkdir,param[1], mode);		
		if (resultado == 0) {
			printf("El directorio fue creado exitosamente.\n \n");
		}
		else {
			perror("Error al crear el directorio");
		}		
	}
}
