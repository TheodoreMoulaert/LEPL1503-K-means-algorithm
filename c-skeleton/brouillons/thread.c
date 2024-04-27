#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
uint32_t tailleBuffers;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;


// Producteur
void producer(void){
    int item;
    while(true){
        item=produce(item);
        sem_wait(&empty); // attente d’une place libre
        pthread_mutex_lock(&mutex);
        // section critique
        insert_item();
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // il y a une place remplie en plus
    }
}

// Consommateur
void consumer(void){
    int item;
    while(true){
        sem_wait(&full); // attente d’une place remplie
        pthread_mutex_lock(&mutex);
        // section critique
        item=remove(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // il y a une place libre en plus
    }
}

