#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

void main(int argc, char *param[]){
	int file_descriptor;
    
    if(param[1]==NULL)
        printf("Falta un introducir un parametro.\n \n");
	else {
    
        file_descriptor = syscall(SYS_open, param[1], O_CREAT );

        if (file_descriptor == -1)
            perror("Error al abrir el archivo \n \n");
        else{
            printf("Archivo fue creado exitosamente.\n \n");
            syscall(SYS_close, file_descriptor);
        }
    }
}
