#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void *producer();
void *consumer();

sem_t empty, sm, full;
int data, in = 0, out = 0;
int buffer[5];

int main() {
    pthread_t ptid[5], ctid[5];

    printf("\nMain started");

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    sem_init(&sm, 0, 1);

    for (int i = 0; i < 5; i++) {
        pthread_create(&ctid[i], NULL, consumer, NULL);
        pthread_create(&ptid[i], NULL, producer, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(ctid[i], NULL);
        pthread_join(ptid[i], NULL);
    }

    printf("\nMain done\n");
    return 0;
}

void *producer() {
    int produced;

    printf("\nProducer created");

    sem_wait(&empty);
    sem_wait(&sm);

    printf("Enter a number: ");
    scanf("%d", &produced);

    buffer[in] = produced;

    sem_post(&sm);
    sem_post(&full);

    printf("\nProducer: %d", buffer[in]);

    in = (in + 1) % 5;

    return NULL;
}

void *consumer() {
    int total = 0;

    printf("\nConsumer created");

    sem_wait(&full);
    sem_wait(&sm);

    total += buffer[out];

    sem_post(&sm);
    sem_post(&empty);

    printf("\nConsumed: %d", buffer[out]);
    out = (out + 1) % 5;

    printf("\nThe total consumed value is %d\n", total);

    return NULL;
}
