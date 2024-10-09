#!/bin/bash

# Nombre del archivo a compilar y ejecutar
ARCHIVO="shell"
ARCHIVO0="operacion0"
ARCHIVO1="operacion1"
ARCHIVO2="operacion2"
ARCHIVO3="operacion3"
ARCHIVO4="operacion4"
ARCHIVO5="operacion5"
ARCHIVO6="operacion6"
ARCHIVO7="operacion7"


# Si no existe, se crea la carpeta "bin" para guardar el ejecutable
# La carpeta "bin" ya está agregada al ".gitignore"
mkdir -p bin/operaciones

# Compilar, y en caso de que no haya errores, ejecutar
gcc "$ARCHIVO".c -o "bin/$ARCHIVO"
gcc "$ARCHIVO0".c -o "bin/operaciones/$ARCHIVO0" 
gcc "$ARCHIVO1".c -o "bin/operaciones/$ARCHIVO1" 
gcc "$ARCHIVO2".c -o "bin/operaciones/$ARCHIVO2"
gcc "$ARCHIVO3".c -o "bin/operaciones/$ARCHIVO3"
gcc "$ARCHIVO4".c -o "bin/operaciones/$ARCHIVO4"
gcc "$ARCHIVO5".c -o "bin/operaciones/$ARCHIVO5"
gcc "$ARCHIVO6".c -o "bin/operaciones/$ARCHIVO6"
gcc "$ARCHIVO7".c -o "bin/operaciones/$ARCHIVO7"

./bin/"$ARCHIVO"
