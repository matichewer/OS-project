#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int compararOp(char cadena1[]){      //Compara la cadena de texto pasada por parametro con las operaciones
    int resultado = -1;
    int encontre = 0;
    
    for (int i=0; i<8 && !encontre; i++){
        switch(i){
            
            case 0:         //Si la operacion es "-help"
                if(strcmp(cadena1,"-help")==0) {    
                    resultado=0; 
                    encontre=1;
                }
                break; 
                
            case 1:         //Si la operacion es  "-cdir"
                if(strcmp(cadena1,"-cdir")==0) {    
                    resultado=1; 
                    encontre=1;
                } 
                break; 
                
            case 2:         //Si la operacion es "-rdir"
                if(strcmp(cadena1,"-rdir")==0) { 
                    resultado=2; 
                    encontre=1;
                } 
                break; 
            
            case 3:         //Si la operacion es "-carc" 
                if(strcmp(cadena1,"-carc")==0) { 
                    resultado=3; 
                    encontre=1;
                } 
                break;
            
            case 4:         //Si la operacion es "-ld"    
                if(strcmp(cadena1,"-ld")==0) { 
                    resultado=4; 
                    encontre=1;
                } 
                break;
            
            case 5:          //Si la operacion es "-mcont"
                if(strcmp(cadena1,"-mcont")==0) { 
                    resultado=5; 
                    encontre=1;
                } 
                break;
            
            case 6:          //Si la operacion es "-mperm"
                if(strcmp(cadena1,"-mperm")==0) { 
                    resultado=6; 
                    encontre=1;
                } 
            break;
            
           case 7:          //Si la operacion es "-rarc"
                if(strcmp(cadena1,"-rarc")==0) { 
                    resultado=7; 
                    encontre=1;
                } 
            break; 
        }

    }
    return resultado;                            //Devuelve el numero de la operacion
}




void main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    
    //Declaracion de variable pid para guardar el resultado de fork()
    int pid;
    
    //Declaracion de cadenas de texto utilizadas
    char opcion[100];
    char *operacion;
    char *param1;
    char *param2;

    char fin[]=" ";

    printf("\nBienvenido a la Minishell: Para ver los comandos utilice '-help' \n\n");

    do{
        fgets(opcion, 100, stdin);

        opcion[strlen(opcion)-1] = '\0'; // Se cambia el caracter '\n' que deja la funcion fgets al final de la cadena por el caracter '\0'

        operacion = strtok(opcion, fin); // Se pasa el comando a operacion
        param1 = strtok(NULL, fin);      // Se establece el primer parametro, sino se le asigna nulo
        param2 = strtok(NULL, fin);      // Se establece el segundo parametro, sino se le asigna nulo

 
        if(strcmp(operacion, "-exit")==0){  //Funcion "-exit" de salida
            printf("Gracias por usar la Minishell.\nAutores: Franco Popp y Matias David Schwerdt.\n");
            exit(0);
        }      
        else {
            pid = fork();
            if(pid != 0) {
                waitpid(pid, NULL, 0); // el padre espera al hijo
            }
        }
    } while(pid != 0); //Si es el hijo sale del while

    
    char *argv[] = {operacion, param1, param2, NULL}; // Se crean los parametros para la funcion execve()
    char *env[] = {0};

    switch(compararOp(operacion)){ //Se manda a comparar la operacion ingresada con las operaciones válidas, si no es valida devuelve -1

        case 0:	// Operacion Help
            if (execve("./bin/operaciones/operacion0",argv ,env) == -1) {
                perror("execve"); //Manejo de errores si execve falla
            }
            break;

        case 1:  //Operacion crear directorio
            if (execve("./bin/operaciones/operacion1", argv, env) == -1) {
                perror("execve");   //Manejo de errores si execve falla
            }
            break;

        case 2:	//Operacion eliminar direcorio
            if (execve("./bin/operaciones/operacion2", argv, env) == -1) {
                perror("execve"); //Manejo de errores si execve falla
            }
            break;

        case 3: //Operacion crear archivo
            if (execve("./bin/operaciones/operacion3", argv, env) == -1) {
                perror("execve");  //Manejo de errores si execve falla
            }
            break;

        case 4: //Operacion listar contenido
            if (execve("./bin/operaciones/operacion4", argv, env) == -1) {
                perror("execve"); //Manejo de errores si execve falla
            }
            break;

        case 5:   //Operacion mostrar contenido de un archivo
            if (execve("./bin/operaciones/operacion5", argv, env) == -1) {
                perror("execve"); //Manejo de errores si execve falla
            }
            break;

        case 6: //Operacion modificar permisos
            if (execve("./bin/operaciones/operacion6", argv, env) == -1) {
                perror("execve");  //Manejo de errores si execve falla
            }
            break;
           
        case 7: //Operacion eliminar archivo
            if (execve("./bin/operaciones/operacion7", argv, env) == -1) {
                perror("execve"); //Manejo de errores si execve falla
            }
            break;

        case -1: //Operacion no valida
            printf("La operacion %s no es valida.\n",opcion);
            printf("Para ver la lista de operaciones: -help \n \n");
            break;
    }
    
    exit(0);
}
