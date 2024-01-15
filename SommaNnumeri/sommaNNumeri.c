//Somma di N numeri in un vettore

//Algoritmo con N dimensione del vettore NON esattamente divisibile per p (core)
//in modo tale da poter essere generalizzato

//Utilizzo della 1a strategia

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char**argv) {
    
    int N, i, nloc, t, indice, r, id, step;
    float *a, sum, sumtot = 0;

    //DIMENSIONE N DEL VETTORE
    printf("Inserisci dimensione N del vettore: ");
    scanf("%d", &N);

    srand(time(NULL));
    
    //allocazione vettore input (a)
    a = (float*)calloc(N, sizeof(float));

    //inizializzazione e stampa
    for(i = 0; i < N; i++ )
        a[i] = rand() % 10 + 1;
    printf("Vettore A: \n");
    for(i = 0; i < N; i++)
        printf(" %f  ", a[i]);
    printf("\n");

    //PARALLELIZZAZIONE DEL CALCOLO DELLA SOMMA
    #pragma omp parallel private(nloc, sum, id, step, i) shared(a, N, sumtot, r)
    {
        //NUMERO DI THREAD DEL SISTEMA
        t = omp_get_num_threads();
        //DIMENSIONE LOCALE DEL VETTORE PER CIASCUN THREAD
        nloc = N / t;
        //CALCOLO DEL RESTO NEL CASO IN CUI N (DIMENSIONE) NON FOSSE ESATTAMENTE DIVISIBILE PER P (CORE)
        r = N % t;
        //IDENTIIFCATIVO DI CIASCUN THREAD
        id = omp_get_thread_num();

        //RIDISTRIBUZIONE DELLE SOMME CHE I CORE DEVONO FARE IN PIU
        if(id < r)
        {
            nloc++;
            step = 0;
        }
        else
            step = r;
        
        //INIZIALIZZAZIONE SOMMA LOCALE DI CIASCUN THREAD
        sum = 0;
        //CALCOLO SOMMA LOCALE PER CIASCUN THREAD
        for(i = 0; i < nloc; i++)
        {
            sum = sum + a[i+nloc*omp_get_thread_num()+step];
        }
        //STAMPA INFO PER DEBUG
        printf("sono %d, di %d: numeri %d, resto=%d, la mia somma=%f\n", omp_get_thread_num(), t, nloc, r, sum);
        //AGGIORNAMENTO SOMMA GLOBALE
        sumtot += sum;
    }

    //STAMPA
    printf("somma finale: %f\n", sumtot);

    return 0;
}