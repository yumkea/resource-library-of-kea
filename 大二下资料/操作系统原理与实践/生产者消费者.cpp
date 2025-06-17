#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h>
#include <windows.h>
#define N1 3
#define N2 4
#define N 3

void *consume()
{
	int id = ++consumer_id;
	while(1)
	{ 
		sleep(1);
		sem_wait(&full_sem);
		pthread_mutex_lock(&mutex);
		out = out % N;
		printf("Consumer $d consume ‰d in %d\n", id, buff[out], out);
		buff[out] = 0;
		++out;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty_sem);
	}
}

void *product()
{
	int id = +product_id;
	while(1)
	{
		sleep(1);
		sem_wait(&empty_sem);
		pthread_mutex_lock(&mutex);
		if(fscanf(fp,"%d",&data)== EOF)
		{
			fseek(fp,O,SEEK_SET);
			fscanf(fp,"%d",&data);
		}
		in = in%N;
		buff[in] = data;
		printf("Producer %d produced %d in %d\n",id,buff[in],in);
		++in;
		pthread_mutex_unlock(&mutex);
		sem_post(&full_sem);
	}
}

int main(void)
{
	pthread_t id1[N1];
	pthread_t id2[N2];
	sem_init(&empty_sem,0,N);
	sem_init(&full_sem,0,0);
	pthread_mutex_init(&mutex,NULL);
	fp= fopen("D:/大学课程/操作系统原理与实践/test.txt","r");
	int i;
	for(int i= 0;i<N1;i++)
	{
		pthread_create(&id1[i],NULL,product,(void *)(&i));
	} 
	for(int i = 0;i <N2;i++)
	{
		pthread_create(&id2[i],NULL,consume,NULL);
	}
	for(i= 0;i<N1;i++)
	{
		pthread_join(id1[i],NULL);
	}
	for(i= 0;i<N2;i++)
	{
		pthread_join(id2[i],NULL);
	}
	return 0;
}
