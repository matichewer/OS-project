#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

void main(int argc,char *param[]){
    
    mode_t new_permissions;  // Nuevos permisos: lectura y escritura para el propietario
    int result;
    int resultado = -1;
    int encontre = 0;

    if(param[1]==NULL)
        printf("Falta un introducir un parametro.\n \n");
    else {

        if(param[2]!=NULL){
            
            for (int i=0; i<3 && !encontre; i++){
                
                switch(i){
                    
                    case 0: 
                        if(strcmp(param[2],"-le")==0) { 
                            resultado=0; 
                            encontre=1; 
                            new_permissions= S_IRUSR;
                        } 
                        break;
                        
                    case 1: 
                        if(strcmp(param[2],"-lees")==0) { 
                            resultado=2; 
                            encontre=1; 
                            new_permissions= S_IRUSR | S_IWUSR;
                        } 
                        break;
                        
                    case 2: 
                        if(strcmp(param[2],"-ej")==0) { 
                            resultado=3; 
                            encontre=1; 
                            new_permissions= S_IXUSR | S_IRUSR;
                        } 
                        break;
                        
                }
            }
        }

        if(resultado==-1)
            printf("Segundo parametro incorrecto, las opciones son '-le', '-ej' y '-lees'.\n \n");
        else {
            result = syscall(SYS_chmod, param[1], new_permissions);     // Llamada al sistema para cambiar los permisos del archivo
            if (result == -1) 
                perror("Error al cambiar los permisos del archivo \n \n");
            else
                printf("Permisos del archivo cambiados correctamente.\n \n");
        }
    }
}

