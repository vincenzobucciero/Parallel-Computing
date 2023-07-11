    //Somma tra vettori - algoritmo N = k*p

    //VERSIONE 1

    #include <stdio.h>
    #include <omp.h>
    #include <stdlib.h>
    #include <time.h>

    /*
        SOMMA TRA VETTORI
        Nucleo computazione full parallel
        1a Versione - size esattamente divisibile per numero di thread
    */

void allocationVector(double **vector, int n);
void fillVector(double *vector, int n);
void printVector(double *vector, int n);
void deallocationVector(double *vector);

int main()
{
    int n, nloc, i, indice;
    int idThread, numThreads;
    double *vectorA, *vectorB, *vectorC;

    printf("Inserisci dimensione per i vettori A e B:  ");
    scanf("%d", &n);

    srand(time(NULL));

    allocationVector(&vectorA, n);
    fillVector(vectorA, n);
    printf("Vettore A:  \n");
    printVector(vectorA, n);  

    allocationVector(&vectorB, n);
    fillVector(vectorB, n);
    printf("Vettore B:  \n");
    printVector(vectorB, n);  

    allocationVector(&vectorC, n);

    #pragma omp parallel private(nloc, i, indice, idThread) shared(vectorA, vectorB, vectorC, numThreads)
    {
        idThread = omp_get_thread_num();
        numThreads = omp_get_num_threads();
        nloc = n / numThreads;

        printf("Hello from thread %d, numThread %d, numeri %d\n", idThread, numThreads, nloc);

        for(i = 0; i < nloc; i++){
            indice = i + nloc * idThread;
            vectorC[indice] = vectorA[indice] + vectorB[indice];
        }
    }

    printf("Vettore somma C:  \n");
    printVector(vectorC, n);

    deallocationVector(vectorA); 
    deallocationVector(vectorB);
    deallocationVector(vectorC);

    return 0;
}

void allocationVector(double **vector, int n) {
    *vector = (double*)calloc(n, sizeof(double));
}

void fillVector(double *vector, int n) {
    for (int i = 0; i < n; i++) {
        vector[i] = rand()%10;
    }
}

void printVector(double *vector, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lf  ", vector[i]);
    }
    printf("\n");
}

void deallocationVector(double *vector) {
    free(vector);
}