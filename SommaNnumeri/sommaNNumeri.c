//Somma N numeri di un vettore - algoritmo N = k*p

//1a STRATEGIA

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void allocationVector(double **vector, int n);
void fillVector(double *vector, int n);
void printVector(double *vector, int n);
void deallocationVector(double *vector);

int main() {
    int i, n, nloc, resto, step;
    double *vector, sum, sumtot;
    int idThread, numThreads;

    double t0, t1, t_tot;

    sumtot = 0;

    printf("Inserisci dimensione del vettore:  ");
    scanf("%d", &n);

    srand(time(NULL));

    allocationVector(&vector, n);
    fillVector(vector, n);
    printf("Vettore:  \n");
    printVector(vector, n);

    t0 = omp_get_wtime();

    #pragma omp parallel private(i, nloc, step, sum, idThread) shared(sumtot, numThreads, resto)
    {
        idThread = omp_get_thread_num();
        numThreads = omp_get_num_threads();
        nloc = n / numThreads;
        resto = n % numThreads;

        if(idThread < resto){
            nloc++;
            step = 0;
        } else {
            step = resto;
        }

        sum = 0;

        for(i = 0; i < nloc; i++) {
            sum = sum + vector[i + nloc * idThread + step];
        }

        #pragma omp critical
        sumtot += sum;
    }

    t1 = omp_get_wtime();

    printf("Somma totale: %lf\n", sumtot);

    t_tot = t1 - t0;

    printf("Tempo t0: %lf\nTempo t1: %lf\nTempo totale: %lf\n", t0, t1, t_tot);
    
    deallocationVector(vector);

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

