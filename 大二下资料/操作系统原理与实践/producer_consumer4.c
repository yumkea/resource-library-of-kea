#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define PRODUCER_NUM 3 //3�������� 
#define CONSUMER_NUM 4 //4�������� 
#define POOL_SIZE  11  //����ش�С 

int pool[POOL_SIZE] = { 0 }; //buffer area
int head = 0; //��������ȡָ�� 
int rear = 0; //������д��ָ�� 

sem_t room_sem; //ͬ���ź�������ʾ�������п��ÿռ� 
sem_t product_sem; //ͬ���ź�������ʾ�������п��ò�Ʒ 
pthread_mutex_t mutex;
int data;
FILE* fp;
void* producer_fun(void* arg) {
	while (1) 
	{
		sleep(1);
		sem_wait(&room_sem);
		pthread_mutex_lock(&mutex);
		//��������������д������ 
        if(fscanf(fp, "%d", &data)==EOF) //ѭ�����ļ� 
		{
			fseek(fp, 0, SEEK_SET);//���ļ�ָ��fpָ���ļ��Ŀ�ͷ 
			fscanf(fp, "%d", &data);
		}
		rear = rear % POOL_SIZE;
		pool[rear] = data;
		printf("������%d ���򻺳���λ��%dд������%d\n", *((int*)arg), rear, pool[rear]);
		++rear;
		printf("��������������%d\n", (rear - head + POOL_SIZE) % POOL_SIZE);
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
		//�����ߴӻ������ж�ȡ���� 
		head = head % POOL_SIZE;
		printf("������%d�Ŵӻ�����λ��%d ��ȡ����%d\n", *((int*)arg), head, pool[head]);
		pool[head] = 0;
		++head;
		printf("���������ڵ�����Ϊ%d\n", (rear- head + POOL_SIZE) % POOL_SIZE);
		pthread_mutex_unlock(&mutex);
		sem_post(&room_sem);
	}

}

int main() {
	pthread_t producer_id[PRODUCER_NUM];
	pthread_t consumer_id[CONSUMER_NUM];
	pthread_mutex_init(&mutex, NULL); //��ʼ�������� 
	int i, j;

	int ret = sem_init(&room_sem, 0, POOL_SIZE - 1);  //��ʼ���ź�room_semΪ��������С 
	if (ret != 0) {
		printf("sem_init error");
		exit(0);
	}

	ret = sem_init(&product_sem, 0, 0); //��ʼ���ź���product_semΪ0����ʼʱ������û������ 

	if (ret != 0) {
		printf("sem_init error");
		exit(0);
	}
               fp = fopen("D:/��ѧ�γ�/����ϵͳԭ����ʵ��/test.txt", "r");
               if(fp == NULL) exit(1);

	for (i = 0; i < PRODUCER_NUM; i++) {
		//�����������߳� 
		int* pid = malloc(sizeof(int));
		*pid = i;
		ret = pthread_create(&producer_id[i], NULL, producer_fun, (void*)pid);
		if (ret != 0) {
			printf("producer_id error");
			exit(0);
		}
	}
	for (j = 0; j < CONSUMER_NUM; j++) {
		//�����������߳� 
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
