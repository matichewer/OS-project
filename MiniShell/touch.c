#include <stdio.h>
#include <string.h>

void main(int argc, char *param[]){
	FILE *f;
    char file[100];
    if (param[1]==NULL) {
        printf("Falta un introducir un parametro.\n \n");
    }
	else {    
      	strncpy(file, param[1], sizeof(file));
		f = fopen(file, "w+");
        if (f == NULL){
            perror("Error al abrir el archivo");
        } else {
            printf("Archivo fue creado exitosamente.\n\n");
        }
	fclose(f);
    }
}
