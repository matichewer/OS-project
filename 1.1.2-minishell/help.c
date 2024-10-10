#include <stdio.h>
#include <stdlib.h>

void main(){			
	printf("  exit\n");
	printf("        Sale de la Shell\n\n");	
			
	printf("  mkdir.\n");
	printf("        Crea un directorio\n");
	printf("        Guia de uso: -cdir [ruta/Nombre_del_directorio]\n\n");
		
	printf("  rm_dir\n");
	printf("        Elimina un directorio\n");
	printf("        Guia de uso: -rdir [ruta/Nombre_del_directorio]\n\n");

	printf("  rm_file\n");
	printf("        Elimina un archivo\n");
	printf("        Guia de uso: -rarc [ruta/Nombre_del_archivo]\n\n");
		
	printf("  touch\n");
	printf("        Crea un archivo\n");
	printf("        Guia de uso: -carc [ruta/Nombre_del_archivo]\n\n");
		
	printf("  ls\n");
	printf("        Lista el contenido de un directorio\n");
	printf("        Guia de uso: -ld [ruta/Nombre_del_directorio]\n");
	printf("        Se listara el directorio actual si no se ingreso ningun parametro\n\n");
		
	printf("  cat\n");
	printf("        Visualizar el contenido de un un archivo\n");
	printf("        Guia de uso: -mcont [ruta/Nombre_del_archivo]\n\n");
		
	printf("  chmod\n");
	printf("        Modifica los permisos de un archivo\n");
	printf("        Guia de uso: -mperm [ruta/Nombre_del_archivo] [Permiso]\n");
	printf("        Los comandos de los [permisos] son:\n");
	printf("            Escritura: '-le'\n");
	printf("            Lectura: '-es'\n");
	printf("            Ejecucion: '-ej'\n");
	printf("            Lectura y escritura: '-lees'\n\n");	
}
