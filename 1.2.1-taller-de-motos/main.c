#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t armar_ruedas;
sem_t armar_cuadro;
sem_t agregar_motor;
sem_t pintar_moto;
sem_t equipar_moto;

// Funciones de cada operario
void* operario_arma_ruedas(void* arg) {
    while(1) {
        sem_wait(&armar_ruedas);
        printf("Armando ruedas...\n");
        sleep(1);
        sem_post(&armar_cuadro);
    }
}

void* operario_arma_cuadro(void* arg) {
    while(1) {
        sem_wait(&armar_cuadro);
        printf("Armando cuadro...\n");
        sleep(1);
        sem_post(&agregar_motor); 
    }
}

void* operario_agrega_motor(void* arg) {
    while(1){
        sem_wait(&agregar_motor);        
        printf("Agregando motor...\n");
        sleep(1);
        sem_post(&pintar_moto);
    }
}

void* operario_pinta_rojo(void* arg) {
    while(1) {
        sem_wait(&pintar_moto);        
        printf("Pintando moto de rojo...\n");
        sleep(1);
        sem_post(&equipar_moto);
    }    
}

void* operario_pinta_verde(void* arg) {
    while(1) {
        sem_wait(&pintar_moto);        
        printf("Pintando moto de verde...\n");
        sleep(1);
        sem_post(&equipar_moto);
    }
}

void* operario_equipa_moto(void* arg) {
    while(1){
        sem_wait(&equipar_moto);
        printf("No hay equipamiento extra, comenzando a armar otra moto...\n\n");
        sleep(1);
        sem_post(&armar_ruedas);

        sem_wait(&equipar_moto);    
        printf("Equipando moto...\n\n");
        sleep(1);
        sem_post(&armar_ruedas);
    }
}

int main() {
    pthread_t operarios[6];

    sem_init(&armar_ruedas, 0, 1);
    sem_init(&armar_cuadro, 0, 0);
    sem_init(&agregar_motor, 0, 0);
    sem_init(&pintar_moto, 0, 0);
    sem_init(&equipar_moto, 0, 0);

    pthread_create(&operarios[0], NULL, operario_arma_ruedas, NULL);
    pthread_create(&operarios[1], NULL, operario_arma_cuadro, NULL);
    pthread_create(&operarios[2], NULL, operario_agrega_motor, NULL);
    pthread_create(&operarios[3], NULL, operario_pinta_rojo, NULL);
    pthread_create(&operarios[4], NULL, operario_pinta_verde, NULL);
    pthread_create(&operarios[5], NULL, operario_equipa_moto, NULL);

    for (int i = 0; i < 6; i++) {
        pthread_join(operarios[i], NULL);
    }

    sem_destroy(&armar_ruedas);
    sem_destroy(&armar_cuadro);
    sem_destroy(&agregar_motor);
    sem_destroy(&pintar_moto);
    sem_destroy(&equipar_moto);

    return 0;
}
