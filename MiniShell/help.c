#include <stdio.h>
#include <stdlib.h>

void main(){			
	printf("  exit\n");
	printf("        Sale de la Shell\n\n");	
			
	printf("  mkdir\n");
	printf("        Crea un directorio\n");
	printf("        Guia de uso: mkdir [ruta/Nombre_del_directorio]\n\n");
		
	printf("  rm_dir\n");
	printf("        Elimina un directorio\n");
	printf("        Guia de uso: rm_dir [ruta/Nombre_del_directorio]\n\n");

	printf("  rm_file\n");
	printf("        Elimina un archivo\n");
	printf("        Guia de uso: rm_file [ruta/Nombre_del_archivo]\n\n");
		
	printf("  touch\n");
	printf("        Crea un archivo\n");
	printf("        Guia de uso: touch [ruta/Nombre_del_archivo]\n\n");
		
	printf("  ls\n");
	printf("        Lista el contenido de un directorio. Si no se ingresa parametro se lista el directorio actual.\n");
	printf("        Guia de uso: ls [ruta/Nombre_del_directorio]\n\n");
		
	printf("  cat\n");
	printf("        Visualizar el contenido de un un archivo\n");
	printf("        Guia de uso: cat [ruta/Nombre_del_archivo]\n\n");
		
	printf("  chmod\n");
	printf("        Modifica los permisos de un archivo\n");
	printf("        Guia de uso: chmod [ruta/Nombre_del_archivo] [Permiso]\n");
	printf("        Los comandos de los [permisos] son:\n");
	printf("            Escritura: '-le'\n");
	printf("            Lectura: '-es'\n");
	printf("            Ejecucion: '-ej'\n");
	printf("            Lectura y escritura: '-lees'\n\n");	
}
