#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_ruedas, sem_chasis, sem_motor, sem_pintura, sem_mejora, sem_ciclo;

void* ruedas_routine();
void* chasis_routine();
void* motor_routine();
void* pintura_verde_routine();
void* pintura_roja_routine();
void* mejora_routine();

int main()
{
    //   1 1 2 3 (4 o 5) 1 1 2 3 (4 o 5) 6
    // AABC(DoE)AABC(DoE)F AABC(DoE)AABC(DoE)F
    pthread_t tid_op1, tid_op2, tid_op3, tid_op4, tid_op5,tid_op6;

    sem_init(&sem_ruedas, 0, 2);
    sem_init(&sem_chasis, 0, 0);
    sem_init(&sem_motor, 0, 0);
    sem_init(&sem_pintura, 0, 0);
    sem_init(&sem_mejora, 0, 1);
    sem_init(&sem_ciclo, 0, 2);

    pthread_create(&tid_op1, NULL, ruedas_routine, NULL);
    pthread_create(&tid_op2, NULL, chasis_routine, NULL);
    pthread_create(&tid_op3, NULL, motor_routine, NULL);
    pthread_create(&tid_op4, NULL, pintura_verde_routine, NULL);
    pthread_create(&tid_op5, NULL, pintura_roja_routine, NULL);
    pthread_create(&tid_op6, NULL, mejora_routine, NULL);

    pthread_join(tid_op1, NULL);
    pthread_join(tid_op2, NULL);
    pthread_join(tid_op3, NULL);
    pthread_join(tid_op4, NULL);
    pthread_join(tid_op5, NULL);
    pthread_join(tid_op6, NULL);

    sem_destroy(&sem_ruedas);
    sem_destroy(&sem_chasis);
    sem_destroy(&sem_motor);
    sem_destroy(&sem_pintura);
    sem_destroy(&sem_mejora);
    sem_destroy(&sem_ciclo);

    return 0;
}

void* ruedas_routine()
{
    while(1)
    {
        sem_wait(&sem_ciclo);
        sem_wait(&sem_ruedas);
        printf("Operario 1 produce: Rueda\n");
        sleep(1);
        sem_post((&sem_chasis));
    }
    return NULL;
}

void* chasis_routine()
{
    while(1)
    {
        sem_wait(&sem_chasis);
        sem_wait(&sem_chasis);
        printf("Operario 2 produce_ Chasis\n");
        sleep(1);
        sem_post(&sem_motor);
    }
    return NULL;
}

void* motor_routine()
{
    while(1)
    {
        sem_wait(&sem_motor);
        printf("Operario 3 produce: Motor\n");
        sleep(1);
        sem_post(&sem_pintura);
    }
    return NULL;
}

void* pintura_verde_routine()
{
    while(1)
    {
        sem_wait(&sem_pintura);
        printf("Operario 4 pinta: Verde\n");
        sleep(1);
        sem_post(&sem_ruedas);
        sem_post(&sem_ruedas);
        sem_post(&sem_mejora);
    }
    return NULL;
}

void* pintura_roja_routine()
{
    while(1)
    {
        sem_wait(&sem_pintura);
        printf("Operario 5 pinta: Rojo\n");
        sleep(1);
        sem_post(&sem_ruedas);
        sem_post(&sem_ruedas);
        sem_post(&sem_mejora);
    }
    return NULL;
}

void* mejora_routine()
{
    while(1)
    {
        sem_wait(&sem_mejora);
        sem_wait(&sem_mejora);
        printf("Operario 6 produce: Mejora\n");
        sleep(1);
        sem_post(&sem_ciclo);
        sem_post(&sem_ciclo);
        sem_post(&sem_ciclo);
        sem_post(&sem_ciclo);
    }
    return NULL;
}

