#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h>

sem_t sem_chopsticks[5];
sem_t sem_eaters;
int PID[5]={0,1,2,3,4};
int number=0;
void sem_signal_init(){
	int i,j,k;
	for(i=0;i<5;i++){
		sem_init(&sem_chopsticks[i],0,1);
		j=sem_init(&sem_chopsticks[i],0,1);
		if(j==-1){
			perror("opps:sem_init error!");
			exit(1);
		}
	}
	sem_init(&sem_eaters,0,4);
	k=	sem_init(&sem_eaters,0,4);
	if(k==-1){
		perror("opps:sem_init error!");
		exit(1);
	}
}
void *doing(void *pid){
	int pthread_id=*(int*)pid%5;
	printf("%d 哲学家思考中------\n",(int)pthread_id);
	sem_wait(&sem_eaters);
	sem_wait(&sem_chopsticks[pthread_id]);
	printf("%d 哲学家拿起了筷子 %d\n",(int)pthread_id,(int)pthread_id);
	sem_wait(&sem_chopsticks[(pthread_id+1)%5]);
	printf("%d 哲学家拿起了筷子 %d\n",(int)pthread_id,((int)pthread_id+1)%5);
	printf("%d 个哲学家正在用餐\n",(int)pthread_id);
	number++;
	printf("%d 个哲学家用完了餐\n",number);
	sem_post(&sem_chopsticks[pthread_id]);
	sem_post(&sem_chopsticks[(pthread_id+1)%5]);
	sem_post(&sem_eaters);
}

int main(){
	int i,j,k,p,q;
	for(i=1;i<=50;i++){
		printf("----------第%d次运行---------\n",i);
		pthread_t ph_threads[5];
		sem_signal_init();
		for(j=0;j<5;j++){
			printf("creating thread %d\n",j);
			pthread_create(&ph_threads[j],NULL,doing, &PID[j]);
			k=pthread_create(&ph_threads[j],NULL,doing, &PID[j]);
			if(k!=0){
				perror("oops:pthread_create error!");
				exit(1);
			}
		}
		for(p=0;p<5;p++){
			pthread_join(ph_threads[p],NULL);
		}
		sem_destroy(&sem_eaters);
		for(q=0;q<5;q++){
			sem_destroy(&sem_chopsticks[q]);
		}
		number=0;
		printf("\n");
	}
	return 0;
}
