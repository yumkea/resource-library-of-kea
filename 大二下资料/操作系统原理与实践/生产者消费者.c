#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFF_MAX 10

sem_t mutex; sem_t empty; sem_t full;

typedef struct{
    char buff[BUFF_MAX][32];
    int head;   
    int tail;   
}Q_Queue, *Queue;
Q_Queue que;
Queue q = &que; 
FILE *fp = NULL;

void EnterQue(Queue queue){
    
    int temp = (queue->tail)+1;
    fread(queue->buff[temp], 8, 4, fp);
    queue->tail = (queue->tail+1) % BUFF_MAX;
    printf("%s\n", queue->buff[temp]);
    printf("-----temp is %d\n", temp);
}
void LeaveQUE(Queue queue){

    int temp = queue->head;
    printf("%s\n", queue->buff[temp]);
    queue->head = (queue->head+1) % BUFF_MAX;
}
void *Producer(void *agrv){
    int i = *(int *)agrv;
    sem_wait(&empty);
    sem_wait(&mutex);
    printf("Producer %d is working\n", i);
    EnterQue(q);
    sem_post(&mutex);
    sem_post(&full);
}

void *Consumer(void *argv){
    int i = *(int *)argv;
    sem_wait(&full);
    sem_wait(&mutex);
    printf("Consumer %d is taking\n", i);
    LeaveQUE(q);
    sem_post(&mutex);
    sem_post(&full);
}

int main(){

    pthread_t producer[3];
    pthread_t consumer[4];

    q->tail = -1;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);

    fp = fopen("D:/大学课程/操作系统原理与实践/test.txt", "r");
    int i;
    for(i=0; i<3; i++){
        pthread_create(&producer[i], NULL, Producer, &i);
        sleep(2);
    }
    for(i=0; i<4; i++){
        pthread_create(&consumer[i], NULL, Consumer, &i);
        sleep(2);
    }

    fclose(fp);
    return 0;
}


