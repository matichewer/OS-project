#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t armar_ruedas, armar_cuadro, agregar_motor, pintar_moto, equipar_moto, sem_ciclo;

// Funciones de ada operario
void* operario_arma_rueda();
void* operario_arma_cuadro();
void* operario_agrega_motor();
void* operario_pinta_verde();
void* operario_pinta_rojo();
void* operario_equipa_moto();

int main()
{
    pthread_t operarios[6];

    sem_init(&armar_ruedas, 0, 2);
    sem_init(&armar_cuadro, 0, 0);
    sem_init(&agregar_motor, 0, 0);
    sem_init(&pintar_moto, 0, 0);
    sem_init(&equipar_moto, 0, 1);
    sem_init(&sem_ciclo, 0, 2);

    pthread_create(&operarios[0], NULL, operario_arma_rueda, NULL);
    pthread_create(&operarios[1], NULL, operario_arma_cuadro, NULL);
    pthread_create(&operarios[2], NULL, operario_agrega_motor, NULL);
    pthread_create(&operarios[3], NULL, operario_pinta_verde, NULL);
    pthread_create(&operarios[4], NULL, operario_pinta_rojo, NULL);
    pthread_create(&operarios[5], NULL, operario_equipa_moto, NULL);

    for(int i = 0; i < 6; i++)
    {
            pthread_join(operarios[i], NULL);
    }

    sem_destroy(&armar_ruedas);
    sem_destroy(&armar_cuadro);
    sem_destroy(&agregar_motor);
    sem_destroy(&pintar_moto);
    sem_destroy(&equipar_moto);
    sem_destroy(&sem_ciclo);

    return 0;
}

void* operario_arma_rueda()
{
    while(1)
    {
        sem_wait(&sem_ciclo);
        sem_wait(&armar_ruedas);
        printf("Operario 1: poniendo una rueda...\n");
        sleep(1);
        sem_post(&armar_cuadro);
    }
    return NULL;
}

void* operario_arma_cuadro()
{
    while(1)
    {
        sem_wait(&armar_cuadro);
        sem_wait(&armar_cuadro);
        printf("Operario 2: armando cuadro...\n");
        sleep(1);
        sem_post(&agregar_motor);
    }
    return NULL;
}

void* operario_agrega_motor()
{
    while(1)
    {
        sem_wait(&agregar_motor);
        printf("Operario 3: agregando motor...\n");
        sleep(1);
        sem_post(&pintar_moto);
    }
    return NULL;
}

void* operario_pinta_verde()
{
    while(1)
    {
        sem_wait(&pintar_moto);
        printf("Operario 4: pintando moto de verde...\n");
        sleep(1);
        sem_post(&armar_ruedas);
        sem_post(&armar_ruedas);
        sem_post(&equipar_moto);
    }
    return NULL;
}

void* operario_pinta_rojo()
{
    while(1)
    {
        sem_wait(&pintar_moto);
        printf("Operario 5: pintando moto de rojo...\n");
        sleep(1);
        sem_post(&armar_ruedas);
        sem_post(&armar_ruedas);
        sem_post(&equipar_moto);
    }
    return NULL;
}

void* operario_equipa_moto()
{
    while(1)
    {
        sem_wait(&equipar_moto);
        sem_wait(&equipar_moto);
        printf("Operario 6: equipando mejora...\n");
        sleep(1);
        sem_post(&sem_ciclo);
        sem_post(&sem_ciclo);
        sem_post(&sem_ciclo);
        sem_post(&sem_ciclo);
    }
    return NULL;
}
