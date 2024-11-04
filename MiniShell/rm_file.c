#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>


void main(int argc, char *param[]){	
	if(param[1]==NULL){
		printf("Falta introducir un parametro.\n\n");
	}
	else {		
		int resultado = syscall(SYS_unlink, param[1]);
		if (resultado == 0){
			printf("Archivo eliminado exitosamente.\n\n");
		} else {
			perror("Error al eliminar el archivo");
		}
	}
}
