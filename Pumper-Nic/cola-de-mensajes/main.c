#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <time.h>

// tipos de mensajes
#define CLIENTEVIP 1
#define CLIENTE 2
#define HAMBURGUESA 3
#define VEGANO 4
#define PAPAS 5

#define CANT_CLIENTES 10
#define START_ID 500
#define KEY ((key_t)(12345))

typedef struct{
    long tipo;
    int menu;
    int id_cliente;
    int vip;
} msg;

char* menu[] = {
    "Hamburguesa",
    "Menu vegano",
    "Papas Fritas"
};

void empleado1();
void empleado2();
void empleado3y4(int id);
void cajero();
void cliente(int id);

int main()
{
    int qid = msgget(KEY, IPC_CREAT | 0666);
    msgctl(qid, IPC_RMID, NULL);

    qid = msgget(KEY, IPC_CREAT | 0666);

    pid_t pid_empleado1 = fork();
    if(pid_empleado1 == 0)
    {
        empleado1();
        exit(0);
    }

    pid_t pid_empleado2 = fork();
    if(pid_empleado2 == 0)
    {
        empleado2();
        exit(0);
    }

    pid_t pid_empleado3 = fork();
    if(pid_empleado3 == 0)
    {
        empleado3y4(3);
        exit(0);
    }

    pid_t pid_empleado4 = fork();
    if(pid_empleado4 == 0)
    {
        empleado3y4(4);
        exit(0);
    }

    pid_t pid_cajero = fork();
    if(pid_cajero == 0)
    {
        cajero();
        exit(0);
    }

    for(int i = 0; i < CANT_CLIENTES; i++)
    {
        pid_t pid_cliente = fork();
        if(pid_cliente == 0)
        {
            cliente(START_ID + i);
            exit(0);
        }
    }

    for(int i = 0; i < CANT_CLIENTES; i++)
    {
        wait(NULL);
    }

    kill(pid_empleado1, SIGKILL);
    kill(pid_empleado2, SIGKILL);
    kill(pid_empleado3, SIGKILL);
    kill(pid_empleado4, SIGKILL);
    kill(pid_cajero, SIGKILL);

    printf("fin\n");
    return 0;
}

void empleado1()
{
    int qid = msgget(KEY, IPC_CREAT | 0666);
    msg pedido;
    while(1)
    {
        msgrcv(qid, &pedido, sizeof(msg) - sizeof(long), HAMBURGUESA, 0);
        printf("El empleado 1 comienza a cocinar una hamburguesa\n");
        usleep(3000);
        pedido.tipo = pedido.id_cliente;
        printf("El empleado 1 entrega la hamburguesa\n");
        msgsnd(qid, &pedido, sizeof(msg) - sizeof(long), 0);
    }
}

void empleado2()
{
    int qid = msgget(KEY, IPC_CREAT | 0666);
    msg pedido;
    while(1)
    {
        msgrcv(qid, &pedido, sizeof(msg) - sizeof(long), VEGANO, 0);
        printf("El empleado 2 comienza a cocinar un menu vegano\n");
        usleep(3000);
        pedido.tipo = pedido.id_cliente;
        printf("El empleado 2 entrega el menu vegano\n");
        msgsnd(qid, &pedido, sizeof(msg) -sizeof(long), 0);
    }
}

void empleado3y4(int id)
{
    int qid = msgget(KEY, IPC_CREAT | 0666);
    msg pedido;
    while(1)
    {
        msgrcv(qid, &pedido, sizeof(msg) - sizeof(long), PAPAS, 0);
        printf("El empleado %i comienza a cocinar unas papas\n", id);
        usleep(3000);
        pedido.tipo = pedido.id_cliente;
        printf("El empleado %i entrega las papas\n", id);
        msgsnd(qid, &pedido, sizeof(msg) - sizeof(long), 0);
    }
}

void cajero()
{
    int qid = msgget(KEY, 0666);
    msg pedido;
    while(1)
    {
        msgrcv(qid, &pedido, sizeof(msg) - sizeof(long), -2, 0);
        printf("Un cliente%s pidio: %s\n", pedido.vip == CLIENTEVIP ? " VIP" : "", menu[pedido.menu - 3]);
        usleep((3000));
        pedido.tipo = pedido.menu;
        printf("El cajero envia el pedido de hamburguesa al empleado\n");
        msgsnd(qid, &pedido, sizeof(msg) - sizeof(long), 0);
    }
}

void cliente(int id)
{
    int qid = msgget(KEY, 0666);
    srand(time(NULL)+getpid());
    msg pedido;
    usleep((rand()%10) + 1);
    pedido.vip = (rand() % 2) + 1;
    pedido.menu = (rand() % 3) + 3;
    pedido.id_cliente = id;
    pedido.tipo = pedido.vip;
    printf("El cliente%s %i pide %s\n", pedido.vip == 2 ? " VIP" : "",id, menu[pedido.menu - 3]);
    msgsnd(qid, &pedido, sizeof(msg) - sizeof(long), 0);
    msgrcv(qid, &pedido, sizeof(msg) - sizeof(long), id, 0);
    printf("El cliente%s %i recibe %s\n", pedido.vip == 2 ? " VIP" : "", id, menu[pedido.menu - 3]);
}