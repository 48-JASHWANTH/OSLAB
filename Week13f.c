#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, writeblock;
int data = 0, readers_count = 0;

void *reader(void *arg) {
    int reader_id = *((int*)arg);
    while (1) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1)
            sem_wait(&writeblock);
        sem_post(&mutex);

        printf("Reader %d read data: %d\n", reader_id, data);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0)
            sem_post(&writeblock);
        sem_post(&mutex);

        sleep(1);
    }
}

void *writer(void *arg) {
    int writer_id = *((int*)arg);
    while (1) {
        sem_wait(&writeblock);

        data++;
        printf("Writer %d wrote data: %d\n", writer_id, data);

        sem_post(&writeblock);

        sleep(1);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
   
    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);
   
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
   
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
   
    for (int i = 0; i < NUM_READERS; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < NUM_WRITERS; i++)
        pthread_join(writers[i], NULL);
   
    sem_destroy(&mutex);
    sem_destroy(&writeblock);
   
    return 0;
}