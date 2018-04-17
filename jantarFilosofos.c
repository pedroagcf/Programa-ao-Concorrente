#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define SIZE 5
#define PENSAR 0
#define FOME 1
#define COMER 2
#define ESQUERDA (numFilo+4)%SIZE
#define DIREITA (numFilo+1)%SIZE

void *filosofo(void *num);
void pegaGarfo(int numFilo);
void liberaGarfo(int numFilo);
void verifica(int numFilo);

sem_t mutex;
sem_t semaf[SIZE];

int estado[SIZE];
int filosofos[SIZE] = {0, 1, 2, 3, 4};

void *filosofo(void *num){
	
	while(1){
	
		int *idFilo = num;
		
		sleep(1 + rand() % 2);
		
		pegaGarfo(*idFilo);
		sleep(1 + rand() % 2);
		
		liberaGarfo(*idFilo);
	}
}

void pegaGarfo(int numFilo){
	
	sem_wait(&mutex);
	
	estado[numFilo] = FOME;
	
	printf("Filosofo %d esta com fome! \n", numFilo+1);
	
	verifica(numFilo);

	sem_post(&mutex);
	sem_wait(&semaf[numFilo]);

	sleep(1 + rand() % 2);
}

void liberaGarfo(int numFilo){

	sem_wait(&mutex);

	estado[numFilo] = PENSAR;
	
	printf("filosofo %d liberou os garfos %d e %d. \n", numFilo+1, ESQUERDA+1, numFilo+1);
	printf("Filosofo %d ta pensando! \n", numFilo+1);
	
	verifica(ESQUERDA);
	verifica(DIREITA);
	
	sem_post(&mutex);

}

void verifica(int numFilo){

	if(estado[numFilo] == FOME && estado[ESQUERDA] != COMER && estado[DIREITA] != COMER){
		
		estado[numFilo] = COMER;
		sleep(1 + rand() % 2);

		printf("Filosofo %d agarrou os garfos %d e %d.\n", numFilo+1, ESQUERDA+1, numFilo+1);
      printf("Filosofo %d esta a comer.\n", numFilo+1);

		sem_post(&semaf[numFilo]);
	}
}

int main(){

	int i;
	pthread_t threadId[SIZE];
	
	sem_init(&mutex, 0, 1);
	
	for(i = 0; i < SIZE; i++)
		sem_init(&semaf[i], 0, 0);

	for(i = 0; i < SIZE; i++){
		
		pthread_create(&threadId[i], NULL, filosofo, &filosofos[i]);
		
		printf("Filosofo %d PENSANDO!\n", i+1);
	}

	for(i = 0; i < SIZE; i++)
		pthread_join(threadId[i], NULL);

	return 0;
}
