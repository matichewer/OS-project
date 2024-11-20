
#include <stdio.h>
#include <string.h>

#define MAX 1000

void main(int argc,char *param[]){

    char dir[100];
        
    if(param[1]==NULL){
        printf("Falta un introducir un parametro.\n \n");
    } else {
        strncpy(dir, param[1], sizeof(dir));
	FILE *f = fopen(dir, "r");
	char leido[MAX];
	if (f != NULL){
		while (fgets(leido, MAX, f) != NULL){
			printf(leido);
		}
	}
	else {  
		printf("Error al abrir el archivo");
          }
	fclose(f);
        
    }
}
