#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define HAMBURGUESA 0
#define VEGANO 1
#define PAPAS 2

#define CANT_CLIENTES 5
#define CANT_CLIENTES_VIP 2

char* menu[] = {
    "Hamburguesa",
    "Menu vegano",
    "Papas Fritas"
};

int pipe_pedido_hamburguesa[2];
int pipe_pedido_vegano[2];
int pipe_pedido_papas[2];

int pipe_cliente_cajero[2];
int pipe_clienteVIP_cajero[2];

int pipe_despacho_hamburguesa[2];
int pipe_despacho_vegano[2];
int pipe_despacho_papas[2];

void empleado1();
void empleado2();
void empleado3y4(int id);
void cajero();
void cliente(int id);
void clienteVIP(int id);

int main()
{
    pipe(pipe_pedido_hamburguesa);
    pipe(pipe_pedido_vegano);
    pipe(pipe_pedido_papas);
    pipe(pipe_cliente_cajero);
    pipe(pipe_clienteVIP_cajero);
    pipe(pipe_despacho_hamburguesa);
    pipe(pipe_despacho_vegano);
    pipe(pipe_despacho_papas);

    // El primer empleado se encarga de cocinar las hamburguesas simples
    pid_t pid_empleado1 = fork();
    if(pid_empleado1 == 0)
    {
        close(pipe_pedido_hamburguesa[1]);
        close(pipe_pedido_vegano[0]);
        close(pipe_pedido_vegano[1]);
        close(pipe_pedido_papas[0]);
        close(pipe_pedido_papas[1]);
        close(pipe_cliente_cajero[0]);
        close(pipe_cliente_cajero[1]);
        close(pipe_clienteVIP_cajero[0]);
        close(pipe_clienteVIP_cajero[1]);
        close(pipe_despacho_hamburguesa[0]);
        close(pipe_despacho_vegano[0]);
        close(pipe_despacho_vegano[1]);
        close(pipe_despacho_papas[0]);
        close(pipe_despacho_papas[1]);

        empleado1();
        exit(0);
    }
    else if(pid_empleado1 < 0)
    {
        perror("Error al crear proceso empleado1\n");
        exit(1);
    }

    // El segudo empleado se encarga de cocinar el menu apto vegano
    pid_t pid_empleado2 = fork();
    if(pid_empleado2 == 0)
    {
        close(pipe_pedido_hamburguesa[0]);
        close(pipe_pedido_hamburguesa[1]);
        close(pipe_pedido_vegano[1]);
        close(pipe_pedido_papas[0]);
        close(pipe_pedido_papas[1]);
        close(pipe_cliente_cajero[0]);
        close(pipe_cliente_cajero[1]);
        close(pipe_clienteVIP_cajero[0]);
        close(pipe_clienteVIP_cajero[1]);
        close(pipe_despacho_hamburguesa[0]);
        close(pipe_despacho_hamburguesa[1]);
        close(pipe_despacho_vegano[0]);
        close(pipe_despacho_papas[0]);
        close(pipe_despacho_papas[1]);

        empleado2();
        exit(0);
    }
    else if(pid_empleado2 < 0)
    {
        perror("Error al crear proceso empleado2\n");
        exit(1);
    }

    // El tercer y cuarto empleado se encarga de cocinar las papas
    pid_t pid_empleado3 = fork();
    if(pid_empleado3 == 0)
    {
        close(pipe_pedido_hamburguesa[0]);
        close(pipe_pedido_hamburguesa[1]);
        close(pipe_pedido_vegano[0]);
        close(pipe_pedido_vegano[1]);
        close(pipe_pedido_papas[1]);
        close(pipe_cliente_cajero[0]);
        close(pipe_cliente_cajero[1]);
        close(pipe_clienteVIP_cajero[0]);
        close(pipe_clienteVIP_cajero[1]);
        close(pipe_despacho_hamburguesa[0]);
        close(pipe_despacho_hamburguesa[1]);
        close(pipe_despacho_vegano[0]);
        close(pipe_despacho_vegano[1]);
        close(pipe_despacho_papas[0]);

        empleado3y4(3);
        exit(0);
    }
    else if(pid_empleado3 < 0)
    {
        perror("Error al crear proceso empleado3\n");
        exit(1);
    }

    pid_t pid_empleado4 = fork();
    if(pid_empleado4 == 0)
    {
        close(pipe_pedido_hamburguesa[0]);
        close(pipe_pedido_hamburguesa[1]);
        close(pipe_pedido_vegano[0]);
        close(pipe_pedido_vegano[1]);
        close(pipe_pedido_papas[1]);
        close(pipe_cliente_cajero[0]);
        close(pipe_cliente_cajero[1]);
        close(pipe_clienteVIP_cajero[0]);
        close(pipe_clienteVIP_cajero[1]);
        close(pipe_despacho_hamburguesa[0]);
        close(pipe_despacho_hamburguesa[1]);
        close(pipe_despacho_vegano[0]);
        close(pipe_despacho_vegano[1]);
        close(pipe_despacho_papas[0]);

        empleado3y4(4);
        exit(0);
    }
    else if(pid_empleado4 < 0)
    {
        perror("Error al crear proceso empleado4\n");
        exit(1);
    }

    pid_t pid_cajero = fork();
    if(pid_cajero == 0)
    {
        close(pipe_pedido_hamburguesa[0]);
        close(pipe_pedido_vegano[0]);
        close(pipe_pedido_vegano[0]);
        close(pipe_cliente_cajero[1]);
        close(pipe_clienteVIP_cajero[1]);
        close(pipe_despacho_hamburguesa[0]);
        close(pipe_despacho_hamburguesa[1]);
        close(pipe_despacho_vegano[0]);
        close(pipe_despacho_vegano[1]);
        close(pipe_despacho_papas[0]);
        close(pipe_despacho_papas[1]);

        cajero();
        exit(0);
    }
    else if(pid_cajero < 0)
    {
        perror("Error al crear proceso cajero\n");
        exit(1);
    }

    for(int i = 0; i < CANT_CLIENTES; i++)
    {
        pid_t pid_cliente = fork();
        if(pid_cliente == 0)
        {
            close(pipe_pedido_hamburguesa[0]);
            close(pipe_pedido_hamburguesa[1]);
            close(pipe_pedido_vegano[0]);
            close(pipe_pedido_vegano[1]);
            close(pipe_pedido_papas[0]);
            close(pipe_pedido_papas[1]);
            close(pipe_cliente_cajero[0]);
            close(pipe_clienteVIP_cajero[0]);
            close(pipe_clienteVIP_cajero[1]);
            close(pipe_despacho_hamburguesa[1]);
            close(pipe_despacho_vegano[1]);
            close(pipe_despacho_papas[1]);

            cliente(i+1);
            exit(0);
        }
        else if(pid_cliente < 0)
        {
            perror("Error al crear proceso cliente\n");
            exit(1);
        }
    }

    for(int i = 0; i < CANT_CLIENTES_VIP; i++)
    {
        pid_t pid_cliente_vip = fork();
        if(pid_cliente_vip == 0)
        {
            close(pipe_pedido_hamburguesa[0]);
            close(pipe_pedido_hamburguesa[1]);
            close(pipe_pedido_vegano[0]);
            close(pipe_pedido_vegano[1]);
            close(pipe_pedido_papas[0]);
            close(pipe_pedido_papas[1]);
            close(pipe_cliente_cajero[0]);
            close(pipe_cliente_cajero[1]);
            close(pipe_clienteVIP_cajero[0]);
            close(pipe_despacho_hamburguesa[1]);
            close(pipe_despacho_vegano[1]);
            close(pipe_despacho_papas[1]);

            clienteVIP(i+1);
            exit(0);
        }
        else if(pid_cliente_vip < 0)
        {
            perror("Error al crear proceso clienteVIP\n");
            exit(1);
        }
    }

    for(int i = 0; i < CANT_CLIENTES + CANT_CLIENTES_VIP; i++)
    {
        wait(NULL);
    }

    kill(pid_empleado1, SIGKILL);
    kill(pid_empleado2, SIGKILL);
    kill(pid_empleado3, SIGKILL);
    kill(pid_empleado4, SIGKILL);
    kill(pid_cajero, SIGKILL);

    printf("fin\n");
}

void empleado1()
{
    while(1)
    {
        int recibe, envia;
        read(pipe_pedido_hamburguesa[0], &recibe, sizeof(recibe));
        printf("El empleado1 comienza a cocinar una hamburguesa\n");
        sleep(3);
        envia = HAMBURGUESA;
        printf("El empleado1 entrega la hamburguesa\n");
        write(pipe_despacho_hamburguesa[1], &envia, sizeof(envia));
    }
}

void empleado2()
{
    while(1)
    {
        int recibe, envia;
        read(pipe_pedido_vegano[0], &recibe, sizeof(recibe));
        printf("El empleado2 comienza a cocinar un menu vegano\n");
        sleep(3);
        envia = VEGANO;
        printf("El empleado2 entrega el menu vegano\n");
        write(pipe_despacho_vegano[1], &envia, sizeof(envia));
    }
}

void empleado3y4(int id)
{
    while(1)
    {
        int recibe, envia;
        read(pipe_pedido_papas[0], &recibe, sizeof(recibe));
        printf("El empleado%i comienza a cocinar unas papas\n", id);
        sleep(3);
        envia = PAPAS;
        printf("El empleado%i entrega las papas\n", id);
        write(pipe_despacho_papas[1], &envia, sizeof(envia));
    }
}

void cajero()
{
    while(1)
    {
        int pedido, envia;

        int flags = fcntl(pipe_clienteVIP_cajero[0], F_GETFL, 0);
        fcntl(pipe_clienteVIP_cajero[0], F_SETFL, flags | O_NONBLOCK);
        if(read(pipe_clienteVIP_cajero[0], &pedido, sizeof(pedido)) > 0)
        {
            printf("Un cliente vip pidio: %s\n", menu[pedido]);
        }
        else
        {
            read(pipe_cliente_cajero[0], &pedido, sizeof(pedido));
            printf("Un cliente pidio: %s\n", menu[pedido]);
        }

        switch(pedido)
        {
            case (HAMBURGUESA):
            {
                envia = HAMBURGUESA;
                printf("El cajero envia el pedido de hamburguesa al empleado 1\n");
                write(pipe_pedido_hamburguesa[1], &envia, sizeof(envia));
                break;
            }
            case (VEGANO):
            {
                envia = VEGANO;
                printf("El cajero envia el pedido de menu vegano al empleado 2\n");
                write(pipe_pedido_vegano[1], &envia, sizeof(envia));
                break;
            }
            case (PAPAS):
            {
                envia = PAPAS;
                printf("El cajero envia el pedido de papas a los empleados 3 y 4\n");
                write(pipe_pedido_papas[1], &envia, sizeof(envia));
                break;
            }
        }
    }
}

void cliente(int id)
{
    srand(time(NULL)*getpid());
    sleep(rand()%5);
    printf("Cliente %i llega al local\n", id);

    int pedido = rand() % 3;
    printf("El cliente %i pide %s\n", id, menu[pedido]);
    write(pipe_cliente_cajero[1], &pedido, sizeof(pedido));

    int retira;
    switch(pedido)
    {
        case (HAMBURGUESA):
        {
            read(pipe_despacho_hamburguesa[0], &retira, sizeof(retira));
            printf("El cliente %i recibe %s\n", id, menu[retira]);
            break;
        }
        case (VEGANO):
        {
            read(pipe_despacho_vegano[0], &retira, sizeof(retira));
            printf("El cliente %i recibe %s\n", id, menu[retira]);
            break;
        }
        case (PAPAS):
        {
            read(pipe_despacho_papas[0], &retira, sizeof(retira));
            printf("El cliente %i recibe %s\n", id, menu[retira]);
            break;
        }
    }
    printf("El cliente %i se va del local\n", id);
}

void clienteVIP(int id)
{
    srand(time(NULL)*getpid());
    sleep(rand()%5);
    printf("Cliente vip %i llega al local\n", id);

    int pedido = rand() % 3;
    printf("El cliente vip %i pide %s\n", id, menu[pedido]);
    write(pipe_clienteVIP_cajero[1], &pedido, sizeof(pedido));

    int retira;
    switch(pedido)
    {
        case (HAMBURGUESA):
        {
            read(pipe_despacho_hamburguesa[0], &retira, sizeof(retira));
            printf("El cliente vip %i recibe %s\n", id, menu[retira]);
            break;
        }
        case (VEGANO):
        {
            read(pipe_despacho_vegano[0], &retira, sizeof(retira));
            printf("El cliente vip %i recibe %s\n", id, menu[retira]);
            break;
        }
        case (PAPAS):
        {
            read(pipe_despacho_papas[0], &retira, sizeof(retira));
            printf("El cliente vip %i recibe %s\n", id, menu[retira]);
            break;
        }
    }
    printf("El cliente vip %i se va del local\n", id);
}