#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// #typedef mergePedro{

	
	


// };

void merge(int vetor[], int inicio, int meio, int fim){

	int init = inicio;
	int init2 = meio + 1;
	int aux = 0;
	int tam = fim - inicio + 1;
	int * vetAux;

	vetAux = (int*) malloc(tam*sizeof(int));

	while(init <= meio && init2 <= fim){

		if (vetor[init] < vetor[init2]){
			
			vetAux[aux] = vetor[init];
			init++;
		
		}else{

			vetAux[aux] = vetor[init2];
			init2++;

		}

		aux++;	
	}

	while(init <= meio){
		
		vetAux[aux] = vetor[init];
		aux++;
		init++;
	}

	while(init2 <= fim){

		vetAux[aux] = vetor[init2];
		aux++;
		init2++;
	}

	for (aux = inicio; aux <= fim; aux++)
		vetor[aux] = vetAux[aux - inicio];
}


void mergeSort(int vetor[], int inicio, int fim){

	if(inicio < fim){

		int meio = (inicio + fim)/2;

		mergeSort(vetor, inicio, meio);
		mergeSort(vetor, meio+1, fim);
		merge(vetor, inicio, meio, fim);	
	}

}



int main(){

	long int inicio, fim;
	int size = 0;
	int i = 0;

	printf("Digite o tamanho do vetor:\n");	
	scanf("%d", &size);

	int vetor[size];

	srand(time(NULL));

	for (i = 0; i < size; i++){

		vetor[i] = 1 + (rand() % 100);
		printf("%d\n", vetor[i]);
	}

	inicio = clock();
	fim = clock();
	
	mergeSort(vetor, 0, size-1);

	for (i = 0; i < size; i++)
		printf("%d\n", vetor[i]);

	printf("Tempo de execuçao dado em segundos do algoritmo: %lf \n", (double) (fim - inicio)/1000000);

	return 0;
}