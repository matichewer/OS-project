#!/bin/bash

# Nombre del archivo a compilar y ejecutar
MAIN="main"

# Si no existe, se crea la carpeta "bin" para guardar el ejecutable
mkdir -p bin/comandos

# Compilar todos los archivos .c excepto el archivo main.c
for archivo in *.c; do
    if [ "$archivo" != "$MAIN.c" ]; then
        # Quitamos la extensión .c del nombre del archivo
        nombre_comando=$(basename "$archivo" .c)
        # Compilamos el archivo y lo colocamos en la carpeta bin/comandos/
        gcc "$archivo" -o "bin/comandos/$nombre_comando"
    fi
done

# Compilar el archivo main.c
gcc "$MAIN".c -o "bin/$MAIN"

# Ejecutar el archivo main
./bin/"$MAIN"
