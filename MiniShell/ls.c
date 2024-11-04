#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


void main(int argc, char *param[]){
    DIR *dir;
    struct dirent *entry;
	
    if(param[1]==NULL) {
		printf("Falta un introducir un parametro.\n \n");
	}
    else {
		dir = opendir(param[1]);

		if (dir == NULL){
			perror("Error al abrir el directorio");
		} else {
			while ((entry = readdir(dir)) != NULL) {
				printf("%s\n", entry->d_name);
			}			
			closedir(dir);
		}
    }
}
