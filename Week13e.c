#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#define N 5
pthread_mutex_t mutex;
pthread_cond_t cond_var[N];
enum {THINKING, HUNGRY, EATING} state[N];

int left(int i){
    return (i+N-1)&N;
}

int right(int i){
    return (i+1)%N;
}

void test(int i){
    if(state[i] == HUNGRY && state[left(i)] != EATING && state[right(i)] != EATING){
        state[i] = EATING;
        printf("Philosopher %d is eating\n",i);
        pthread_cond_signal(&cond_var[i]);
    }
}

void pickup_forks(int i){
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry\n",i);
    test(i);
    if(state[i] != EATING)
        pthread_cond_wait(&cond_var[i],&mutex);
    pthread_mutex_unlock(&mutex);
}

void return_forks(int i){
    pthread_mutex_lock(&mutex);
    state[i] =  THINKING;
    printf("Philosopher %d is thinking\n",i);
    test(left(i));
    test(right(i));
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *arg){
    int *id = (int *)arg;
    while(1){
        usleep(1000000);
        pickup_forks(*id);
        usleep(1000000);
        return_forks(*id);
    }
    return NULL;
}

int main(){
    pthread_t tid[N];
    int ids[N];
    pthread_mutex_init(&mutex,NULL);
    for(int i=0;i<N;i++){
        pthread_cond_init(&cond_var[i],NULL);
        ids[i] = i;
        pthread_create(&tid[i],NULL,philosopher,&ids[i]);
    }
    for(int i=0;i<N;i++){
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    for(int i=0;i<N;i++){
        pthread_cond_destroy(&cond_var[i]);
    }
    return 0;
}
