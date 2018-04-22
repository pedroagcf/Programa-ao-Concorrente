#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{

    int * array;
    int inicio;
    int fim;

}mergInfo;

void merge(int *vetor, int init,int mid, int mid_next,int end){
    
    int i = 0, j = 0, k = 0;
    
    int tam_b = (end+1) - mid_next;
    int tam_a = (mid+1) - init;
    int tam_merge = tam_a + tam_b;
    int vet_merge[tam_merge];

    i = init;
    j = mid_next;

    while((i < mid_next) && (j < end+1)){
        
        if(vetor[i] <= vetor[j]){
            
            vet_merge[k] = vetor[i];
            i++;
        
        }else{
            
            vet_merge[k] = vetor[j];
            j++;
        }

        k++;
    }

    if(i == mid_next){
        
        for(i = j; i < end+1; i++){
           
            vet_merge[k] = vetor[i];
            k++;
        }
    
    }else if(j == (end+1)){
        
        for(j = i; j < mid_next; j++){
            
            vet_merge[k] = vetor[j];
            k++;
        }
    }
    
    j = init;
    
    for(i = 0; i < tam_merge; i++){
        
        vetor[j] = vet_merge[i];
        j++;
    }
}


void * mergeSort(void * arg){

    mergInfo * mergT = (mergInfo *) arg;
    int inicio = mergT->inicio;
    int fim = mergT->fim;

    if(inicio == fim){
        return;
    }

    int meio = (mergT->inicio + mergT->fim)/2;

    pthread_t thread1, thread2;

    //pegando a metade das posiçoes do vetor:
    int begin = inicio;
    int mid = meio;
    int mid_next = meio + 1;
    int end = fim;

    mergInfo mergAux, mergAux2;

    mergAux.array = mergT->array;
    mergAux.inicio = begin;
    mergAux.fim = mid;

    mergAux2.array = mergT->array;
    mergAux2.inicio = mid_next;
    mergAux2.fim = end;

    pthread_create(&thread1, NULL, mergeSort, (void*)&mergAux);
    pthread_create(&thread2, NULL, mergeSort, (void*)&mergAux2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    merge(mergT->array, begin,  mid, mid_next, end);

}

int main(){

    long int inicio, fim;
    int size = 0;
    int i = 0;

    inicio = clock();

    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &size);

    mergInfo merg;
    int vetor[size];

    srand(time(NULL));

    for (i = 0; i < size; i++){

        vetor[i] = 1 + (rand() % 100);
        printf("%d\n", vetor[i]);
    }

    merg.array = vetor;
    merg.inicio = 0;
    merg.fim = size - 1;

    mergeSort((void*) &merg);

    fim = clock();

    for (i = 0; i < size; i++)
        printf("%d\n", merg.array[i]);

    printf("Tempo de execuçao dado em segundos do algoritmo: %lf \n", (double) (fim - inicio)/1000000);

    return 0;
}

