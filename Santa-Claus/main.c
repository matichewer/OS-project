#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define UN_SEGUNDO 1000000

#define CANT_RENOS 9
#define CANT_ELFOS 6
#define GRUPO_ELFOS 3


sem_t sem_despierta_santa;
sem_t sem_elfo_vacio, sem_elfo_lleno, sem_elfo_grupo, sem_elfo_ayudado;
sem_t sem_reno_vacio, sem_reno_grupo, sem_reno_ayudado;

pthread_mutex_t mutex_elfo;
pthread_mutex_t mutex_reno;


void* santa(void* args) {
    while (1) {
        sem_wait(&sem_despierta_santa);
        printf("Santa se despierta\n");
        usleep(UN_SEGUNDO);

        if (sem_trywait(&sem_reno_grupo) != 0) { // si no se pudo hacer el wait, es porque llegaron todos los Renos
            printf("Santa ata Renos al trineo\n");
            for (int i = 0; i < CANT_RENOS; i++) {
                sem_post(&sem_reno_ayudado);
                sem_post(&sem_reno_grupo);
            }
            usleep(UN_SEGUNDO * 2);
            printf("Santa termina de atar los Renos\n");
        } else { // si se pudo hacer el wait, es porque no llegaron todos los Renos

            if (sem_trywait(&sem_elfo_grupo) != 0) { // si no se pudo hacer el wait, es porque hay 3 elfos esperandolo
                printf("Santa ayuda a los Elfos\n");
                for (int i = 0; i < GRUPO_ELFOS; i++) {
                    sem_post(&sem_elfo_ayudado);
                }
                usleep(UN_SEGUNDO * 2);
                printf("Santa termina de ayudar a los Elfos\n");
            } 
        }
        printf("Santa se va a dormir\n");
    }
    return NULL;
}

void* reno(void* args) {
    usleep(UN_SEGUNDO * 3);
    sem_wait(&sem_reno_grupo);
    pthread_mutex_lock(&mutex_reno); // uno solo debe despertar a Santa
    if (sem_trywait(&sem_reno_vacio) != 0) { // el 9no reno debe despertar a Santa
        printf("Reno llega. Ya somos 9, entonces busca a santa\n");
        sem_post(&sem_despierta_santa);
    } else { 
        printf("Reno llega. Espera en la cabaña\n");
    }
    pthread_mutex_unlock(&mutex_reno);

    sem_wait(&sem_reno_ayudado);
    usleep(UN_SEGUNDO * 2);
    printf("Reno enganchado al trineo!\n");

    return NULL;
}

void* elfo(void* args) {
    while (1) {
        if ((rand() % 10) < 5) {
            sem_wait(&sem_elfo_grupo);
            pthread_mutex_lock(&mutex_elfo);
            printf("Elfo tiene un problema\n");
            if (sem_trywait(&sem_elfo_vacio) == 0) { // si se pudo hacer el wait, es porque todavia no son 3 elfos
                sem_post(&sem_elfo_lleno); // suma un elfo al grupo
            } else {
                printf("Elfos: Somos %d elfos, queremos despertar a Santa\n", GRUPO_ELFOS);
                sem_post(&sem_despierta_santa);
                usleep(UN_SEGUNDO);
            }
            pthread_mutex_unlock(&mutex_elfo);

            // Esperar ayuda Santa
            sem_wait(&sem_elfo_ayudado);
            usleep(UN_SEGUNDO);
            printf("Elfo es ayudado por Santa\n");
    

            pthread_mutex_lock(&mutex_elfo);
            if (sem_trywait(&sem_elfo_lleno) == 0) { // si se pudo hacer el wait, es porque ya fueron ayudados 3 elfos
                sem_post(&sem_elfo_vacio); 
            } else {
                printf("Elfo: Soy el ultimo, permito ingresar nuevo grupo elfos\n\n");
                for (int i = 0; i < GRUPO_ELFOS; i++) {
                    sem_post(&sem_elfo_grupo);
                }
                usleep(UN_SEGUNDO);
            }
            pthread_mutex_unlock(&mutex_elfo);
        } else {
            printf("Elfo trabaja sin problemas\n");
            usleep(UN_SEGUNDO * 4);
        }
    }
    return NULL;
}


int main() {
    pthread_t t_santa;
    pthread_t t_reno[CANT_RENOS];
    pthread_t t_elfo[CANT_ELFOS];

    pthread_mutex_init(&mutex_elfo, NULL);
    pthread_mutex_init(&mutex_reno, NULL);

    sem_init(&sem_despierta_santa, 0, 0);

    sem_init(&sem_elfo_vacio, 0, GRUPO_ELFOS-1); // 2 porque el 3ero llama a Santa
    sem_init(&sem_elfo_lleno, 0, 0);
    sem_init(&sem_elfo_grupo, 0, GRUPO_ELFOS);
    sem_init(&sem_elfo_ayudado, 0, 0);

    sem_init(&sem_reno_vacio, 0, CANT_RENOS-1); // 8 porque el 9no llama a Santa
    sem_init(&sem_reno_grupo, 0, CANT_RENOS);
    sem_init(&sem_reno_ayudado, 0, 0);


    pthread_create(&t_santa, NULL, santa, NULL);
    for (int i=0; i<CANT_ELFOS; i++) {
        pthread_create(&t_elfo[i], NULL, elfo, NULL);
    }
    usleep(UN_SEGUNDO * 2);
    for (int i=0; i<CANT_RENOS; i++) {
        pthread_create(&t_reno[i], NULL, reno, NULL);
    }

    pthread_join(t_santa, NULL);
    for (int i=0; i<CANT_RENOS; i++) {
        pthread_join(t_reno[i], NULL);
    }
    for (int i=0; i<CANT_ELFOS; i++) {
        pthread_join(t_elfo[i], NULL);
    }

    pthread_mutex_destroy(&mutex_elfo);
    pthread_mutex_destroy(&mutex_reno);

    sem_destroy(&sem_despierta_santa);
    sem_destroy(&sem_elfo_vacio);
    sem_destroy(&sem_elfo_lleno);
    sem_destroy(&sem_elfo_grupo);
    sem_destroy(&sem_elfo_ayudado);
    sem_destroy(&sem_reno_vacio);
    sem_destroy(&sem_reno_grupo);
    sem_destroy(&sem_reno_ayudado);

    return 0;
}
