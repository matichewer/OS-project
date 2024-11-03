#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>


void main(int argc,char *param[]){

    int file_descriptor;
    char buffer[1024];  // Buffer para almacenar los datos leídos
    ssize_t bytes_read;
        
    if(param[1]==NULL){
        printf("Falta un introducir un parametro.\n \n");
    } else {
        file_descriptor = syscall(SYS_open, param[1], O_RDONLY);
        if (file_descriptor == -1){ 
            perror("Error al abrir el archivo \n \n");
        } else {
            bytes_read = syscall(SYS_read, file_descriptor, buffer, sizeof(buffer));
            if (bytes_read == -1){ 
                perror("Error al leer el archivo \n \n");
            } else {
                write(STDOUT_FILENO, buffer, bytes_read); 
                syscall(SYS_close, file_descriptor);
            }
        }
    }
}
