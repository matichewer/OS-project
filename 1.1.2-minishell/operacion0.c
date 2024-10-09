#include <stdio.h>
#include <stdlib.h>

void main(){
	
	printf("\n-------------------------------------------------- \n");
	printf("Operaciones:\n");
	printf("-------------------------------------------------- \n \n");	
		
	printf("0. -exit.\n");
	printf("Sale de la Shell\n \n");	
			
	printf("1. -cdir.\n");
	printf("Crea un directorio\n");
	printf("Guia de uso: -cdir [ruta/Nombre_del_directorio]\n \n");
		
	printf("2. -rdir.\n");
	printf("Elimina un directorio\n");
	printf("Guia de uso: -rdir [ruta/Nombre_del_directorio]\n \n");
		
	printf("3. -carc.\n");
	printf("Crea un archivo\n");
	printf("Guia de uso: -carc [ruta/Nombre_del_archivo]\n \n");
		
	printf("4. -ld.\n");
	printf("Lista el contenido de un directorio\n");
	printf("Guia de uso: -ld [ruta/Nombre_del_directorio]\n");
	printf("Se listara el directorio actual si no se ingreso ningun parametro\n \n");
		
	printf("5. -mcont.\n");
	printf("Visualizar el contenido de un un archivo\n");
	printf("Guia de uso: -mcont [ruta/Nombre_del_archivo]\n \n");
		
	printf("6. -mperm.\n");
	printf("Modifica los permisos de un archivo\n");
	printf("Guia de uso: -mperm [ruta/Nombre_del_archivo] [Permiso]\n");
	printf("Los comandos de los [permisos] son:\n Escritura: '-le' \n Lectura:'-es'\n Ejecucion: '-ej'\n Lectura y escritura:'-lees' \n \n");
	
	printf("7. -rarc.\n");
	printf("Elimina un archivo\n");
	printf("Guia de uso: -rarc [ruta/Nombre_del_archivo]\n \n");
	
}
