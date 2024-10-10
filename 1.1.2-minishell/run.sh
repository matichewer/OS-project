#!/bin/bash


# Nombre del archivo a compilar y ejecutar
MAIN="main"
HELP="help"
ARCHIVO1="operacion1"
ARCHIVO2="operacion2"
ARCHIVO3="operacion3"
ARCHIVO4="operacion4"
ARCHIVO5="operacion5"
ARCHIVO6="operacion6"
ARCHIVO7="operacion7"


# Si no existe, se crea la carpeta "bin" para guardar el ejecutable
# La carpeta "bin" ya está agregada al ".gitignore"
mkdir -p bin/comandos

# Compilar, y en caso de que no haya errores, ejecutar
gcc "$MAIN".c -o "bin/$MAIN"
gcc "$HELP".c -o "bin/comandos/$HELP" 
gcc "$ARCHIVO1".c -o "bin/comandos/$ARCHIVO1" 
gcc "$ARCHIVO2".c -o "bin/comandos/$ARCHIVO2"
gcc "$ARCHIVO3".c -o "bin/comandos/$ARCHIVO3"
gcc "$ARCHIVO4".c -o "bin/comandos/$ARCHIVO4"
gcc "$ARCHIVO5".c -o "bin/comandos/$ARCHIVO5"
gcc "$ARCHIVO6".c -o "bin/comandos/$ARCHIVO6"
gcc "$ARCHIVO7".c -o "bin/comandos/$ARCHIVO7"

./bin/"$MAIN"
