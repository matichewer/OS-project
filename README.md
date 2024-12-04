# Proyecto de Sistemas Operativos

Este repositorio contiene la implementación y documentación de un conjunto problemas relacionados con **Procesos**, **Threads**, **Sincronización**, y conceptos de **Sistemas Operativos**. Los experimentos se realizaron en lenguaje C.

## Contenido del Proyecto

### 1. Procesos, Threads y Comunicación
- **Pumper Nic**: Simulación de un sistema de pedidos para una cadena de comida rápida, implementado utilizando:
  - **Procesos** y **Pipes**.
  - **Colas de Mensajes** para comparar enfoques.
- **Mini Shell**: Implementación de un shell que soporta los siguientes comandos:
  - Mostrar ayuda (`help`).
  - Crear y eliminar directorios (`mkdir` y `rmdir`).
  - Crear un archivo (`touch`).
  - Listar el contenido de un directorio (`ls`).
  - Mostrar el contenido de un archivo (`cat`).
  - Modificar permisos de un archivo (`chmod`).

### 2. Sincronización
- **Taller de Motos**: Simulación de un proceso de ensamblaje de motos utilizando **hilos** y **semáforos**.
- **Santa Claus**: Implementación de un modelo donde Santa interactúa con renos y elfos utilizando **hilos** y **semáforos**.

### 3. Problemas Conceptuales
- **Gestión de Memoria**:
  - Traducción de direcciones lógicas bajo esquemas de paginación y segmentación.
  - Ejemplos de fallos de página y uso del algoritmo de reemplazo **LRU**.
- **Seguridad**:
  - Caso de estudio de CrowdStrike.

## Estructura del Repositorio
La estructura del repositorio es la siguiente:

```bash
├── CrowdStrike.pdf
├── Enunciado.pdf
├── Informe.pdf
├── MiniShell
│   ├── cat.c
│   ├── chmod.c
│   ├── clean.sh
│   ├── help.c
│   ├── ls.c
│   ├── main.c
│   ├── mkdir.c
│   ├── rm_dir.c
│   ├── run.sh
│   └── touch.c
├── Pumper-Nic
│   ├── cola-de-mensajes
│   │   ├── main.c
│   │   └── run.sh
│   └── pipes
│       ├── main.c
│       └── run.sh
├── README.md
├── Santa-Claus
│   ├── main.c
│   └── run.sh
└── Taller-de-motos
    ├── main.c
    └── run.sh
```



