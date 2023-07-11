//Somma tra vettori - algoritmo N = k*p

//VERSIONE 2

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

/*
    SOMMA TRA VETTORI
    Nucleo computazione full parallel
    2a Versione - size NON esattamente divisibile per numero di thread (step e resto)
*/

void allocationVector(double **vector, int n);
void fillVector(double *vector, int n);
void printVector(double *vector, int n);
void deallocationVector(double *vector);

int main() {
    int n, i, indice, nloc, resto, step;
    double *vectorA, *vectorB, *vectorC;
    int idThread, numThreads;

    printf("Inserisci dimensione dei vettori A e B:  ");
    scanf("%d", &n);

    allocationVector(&vectorA, n);
    allocationVector(&vectorB, n);
    allocationVector(&vectorC, n);

    srand(time(NULL));

    fillVector(vectorA, n);
    fillVector(vectorB, n);

    printf("Vettore A:  \n");
    printVector(vectorA, n);
    printf("Vettore B:  \n");
    printVector(vectorB, n);

    #pragma omp parallel private(i, nloc, indice, idThread, step) shared(vectorA, vectorB, vectorC, numThreads, resto)
    {
        /**
         * Se il size del vettore non è divisibile per il numero dei thread che ci sono
         * le locazioni vengono ri-distribuite ai thread che hanno id strettamente minore
         * al resto della divisione del size del vettore ed il numero dei thread.
        */
        idThread = omp_get_thread_num();
        numThreads = omp_get_num_threads();
        nloc = n / numThreads;
        resto = n % numThreads;

        if (idThread < resto) {
            nloc++;
            step = 0;
        } else {
            step = resto;
        }

        //Stampa prova per vedere i thread quanti numeri sommano
        printf("Hello from thread %d, numThreads %d, coppia di numeri sommati %d, resto %d, step %d\n", idThread, numThreads, nloc, resto, step);

        for(i = 0; i < nloc; i++) {
            indice = i + nloc * idThread + step;
            vectorC[indice] = vectorA[indice]+vectorB[indice];
        }
    }

    printf("Vettore somma C:  \n");
    printVector(vectorC, n);

    deallocationVector(vectorA);
    deallocationVector(vectorB);
    deallocationVector(vectorC);

    return 0;
}

void allocationVector(double **vector, int n){
    *vector = (double*)calloc(n, sizeof(double));
}

void fillVector(double *vector, int n){
    for(int i = 0; i < n; i++){
        vector[i] = rand()%10;
    }
}

void printVector(double *vector, int n){
    for(int i = 0; i < n; i++){
        printf("%lf  ", vector[i]);
    }
    printf("\n");
}

void deallocationVector(double *vector){
    free(vector);
}