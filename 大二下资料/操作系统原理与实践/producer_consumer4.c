#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define PRODUCER_NUM 3 //3个生产者 
#define CONSUMER_NUM 4 //4个消费者 
#define POOL_SIZE  11  //缓冲池大小 

int pool[POOL_SIZE] = { 0 }; //buffer area
int head = 0; //缓冲区读取指针 
int rear = 0; //缓冲区写入指针 

sem_t room_sem; //同步信号量，表示缓冲区有可用空间 
sem_t product_sem; //同步信号量，表示缓冲区有可用产品 
pthread_mutex_t mutex;
int data;
FILE* fp;
void* producer_fun(void* arg) {
	while (1) 
	{
		sleep(1);
		sem_wait(&room_sem);
		pthread_mutex_lock(&mutex);
		//生产者往缓冲区写入数据 
        if(fscanf(fp, "%d", &data)==EOF) //循环读文件 
		{
			fseek(fp, 0, SEEK_SET);//把文件指针fp指向文件的开头 
			fscanf(fp, "%d", &data);
		}
		rear = rear % POOL_SIZE;
		pool[rear] = data;
		printf("生产者%d 号向缓冲区位置%d写入数据%d\n", *((int*)arg), rear, pool[rear]);
		++rear;
		printf("缓冲区现在容量%d\n", (rear - head + POOL_SIZE) % POOL_SIZE);
		pthread_mutex_unlock(&mutex);
		sem_post(&product_sem);
	}
}

void* consumer_fun(void* arg) {
	while (1) {
		int data;
		sleep(2);
		sem_wait(&product_sem);
		pthread_mutex_lock(&mutex);
		//消费者从缓冲区中读取数据 
		head = head % POOL_SIZE;
		printf("消费者%d号从缓冲区位置%d 读取数据%d\n", *((int*)arg), head, pool[head]);
		pool[head] = 0;
		++head;
		printf("缓冲区现在的容量为%d\n", (rear- head + POOL_SIZE) % POOL_SIZE);
		pthread_mutex_unlock(&mutex);
		sem_post(&room_sem);
	}

}

int main() {
	pthread_t producer_id[PRODUCER_NUM];
	pthread_t consumer_id[CONSUMER_NUM];
	pthread_mutex_init(&mutex, NULL); //初始化互斥量 
	int i, j;

	int ret = sem_init(&room_sem, 0, POOL_SIZE - 1);  //初始化信号room_sem为缓冲区大小 
	if (ret != 0) {
		printf("sem_init error");
		exit(0);
	}

	ret = sem_init(&product_sem, 0, 0); //初始化信号量product_sem为0，开始时缓冲区没有数据 

	if (ret != 0) {
		printf("sem_init error");
		exit(0);
	}
               fp = fopen("D:/大学课程/操作系统原理与实践/test.txt", "r");
               if(fp == NULL) exit(1);

	for (i = 0; i < PRODUCER_NUM; i++) {
		//创建生产者线程 
		int* pid = malloc(sizeof(int));
		*pid = i;
		ret = pthread_create(&producer_id[i], NULL, producer_fun, (void*)pid);
		if (ret != 0) {
			printf("producer_id error");
			exit(0);
		}
	}
	for (j = 0; j < CONSUMER_NUM; j++) {
		//创建消费者线程 
		int* cid = malloc(sizeof(int));
		*cid = j;
		ret = pthread_create(&consumer_id[j], NULL, consumer_fun, (void*)cid);
		if (ret != 0) {
			printf("consumer_id error");
			exit(0);
		}
	}

	for (i = 0; i < PRODUCER_NUM; i++) {
		pthread_join(producer_id[i], NULL);
		pthread_join(consumer_id[j], NULL);
	}
	exit(0); 
}
