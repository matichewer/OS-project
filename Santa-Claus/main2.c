#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h>
#include <time.h>
#include <unistd.h> 

#define COLOR_VERDE  "\x1b[32m" // para Elfos
#define COLOR_MARRON "\x1b[38;5;94m" // para Renos
#define COLOR_ROJO   "\x1b[31m" // para Santa
#define COLOR_NORMAL  "\x1b[0m"  // Para resetear el color

#define CANT_RENOS 9
#define CANT_ELFOS 6

#define UN_SEGUNDO 1000000

sem_t elfosOrenos, renosListos, elfosConProblemas, armarTrineo, santaAyudaElfo,
renosEnPoloNorte, elfosParaDespertarASanta; 

pthread_mutex_t mutexRenos, mutexElfos;

void *santa(void *arg) { 
    while (1) { 
        printf(COLOR_ROJO"Santa se va a dormir\n"COLOR_NORMAL);
        sem_wait(&elfosOrenos);
        
        if(sem_trywait(&renosListos) == 0){
            printf(COLOR_ROJO"Santa arma el trineo\n"COLOR_NORMAL);
            usleep(UN_SEGUNDO * 2);
            sem_post(&armarTrineo); 
            sem_post(&armarTrineo); 
            sem_post(&armarTrineo); 
            sem_post(&armarTrineo); 
            sem_post(&armarTrineo); 
            sem_post(&armarTrineo); 
            sem_post(&armarTrineo); 
            sem_post(&armarTrineo); 
            sem_post(&armarTrineo);
            printf(COLOR_ROJO"Santa terminó de prepara el trineo y se fue\n"COLOR_NORMAL);
            usleep(UN_SEGUNDO * 3);
        }
        else {
            
            if(sem_trywait(&elfosConProblemas) == 0){ 
                printf(COLOR_ROJO"Santa ayuda a los elfos\n"COLOR_NORMAL);
                usleep(UN_SEGUNDO);
                sem_post(&santaAyudaElfo); 
                sem_post(&santaAyudaElfo); 
                sem_post(&santaAyudaElfo);
            }
        }
    } 
} 

void *reno(void *arg) { 
    int time;
    
    while (1) { 
        
        printf(COLOR_MARRON"Reno de vacaciones en el tropico\n"COLOR_NORMAL); 
        time = rand()%5 + 5;
        usleep(UN_SEGUNDO * time);
        printf(COLOR_MARRON"Reno volvió al polo norte\n"COLOR_NORMAL);
        
        sem_wait(&renosEnPoloNorte);
        pthread_mutex_lock(&mutexRenos);
        if(sem_trywait(&renosEnPoloNorte) != 0){ // Si es el ultimo reno
            sem_post(&elfosOrenos);
            sem_post(&renosListos); // Avisa a santa
        }
        else {
            sem_post(&renosEnPoloNorte);
        }
        pthread_mutex_unlock(&mutexRenos);

        sem_wait(&armarTrineo);
        usleep(UN_SEGUNDO * 3);
        
    } 

} 

void *elfo(void *arg) { 
    int time;
    
    while (1) { 
        
        printf(COLOR_VERDE"Elfo trabajando\n"COLOR_NORMAL); 
        time = rand()%15+5;
        sleep(time);
        printf(COLOR_VERDE"Elfo tiene problemas\n"COLOR_NORMAL); 
        
        pthread_mutex_lock(&mutexElfos);
        sem_wait(&elfosParaDespertarASanta); // De 3
        
        if(sem_trywait(&elfosParaDespertarASanta) != 0){ // Si es el 3er elfo del grupo
            sem_post(&elfosOrenos);
            sem_post(&elfosConProblemas); // Avisa a santa
            printf(COLOR_VERDE"Elfos piden ayuda a santa\n"COLOR_NORMAL);
        }
        else {
            sem_post(&elfosParaDespertarASanta);
        }
        pthread_mutex_unlock(&mutexElfos);
        
        sem_wait(&santaAyudaElfo); // Espera la ayuda de santa
        sem_post(&elfosParaDespertarASanta);
        printf(COLOR_VERDE"Elfo solucionó sus problemas con santa y vuelve a trabajar\n"COLOR_NORMAL);
        
    }
}


int main() { 

    pthread_t threadRenos[CANT_RENOS], threadElfos[CANT_ELFOS], threadSanta;
    
    pthread_mutex_init(&mutexRenos, NULL); 
    pthread_mutex_init(&mutexElfos, NULL);
    
    sem_init(&elfosOrenos, 0, 0); 
    sem_init(&renosListos, 0, 0); 
    sem_init(&elfosConProblemas, 0, 0); 
    sem_init(&armarTrineo, 0, 0); 
    sem_init(&santaAyudaElfo, 0, 0); 
    sem_init(&renosEnPoloNorte, 0, 9); 
    sem_init(&elfosParaDespertarASanta, 0, 3); 
    
    for(int i = 0; i < CANT_RENOS; i++){
        pthread_create(&threadRenos[i], NULL, reno, NULL);
    }
    for(int i = 0; i < CANT_ELFOS; i++){
        pthread_create(&threadElfos[i], NULL, elfo, NULL);
    }
    pthread_create(&threadSanta, NULL, santa, NULL);



    for(int i = 0; i < CANT_RENOS; i++){
        pthread_join(threadRenos[i], NULL);
    }
    for(int i = 0; i < CANT_ELFOS; i++){
        pthread_join(threadElfos[i], NULL);
    }
    pthread_join(threadSanta, NULL);

    pthread_mutex_destroy(&mutexElfos);
    pthread_mutex_destroy(&mutexRenos);
    
    sem_destroy(&elfosOrenos); 
    sem_destroy(&renosListos); 
    sem_destroy(&elfosConProblemas); 
    sem_destroy(&armarTrineo); 
    sem_destroy(&santaAyudaElfo); 
    sem_destroy(&renosEnPoloNorte); 
    sem_destroy(&elfosParaDespertarASanta); 
    
    return 0;
} 