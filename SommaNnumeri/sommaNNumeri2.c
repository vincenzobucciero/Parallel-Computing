//Somma di N numeri in un vettore

//Algoritmo con N dimensione del vettore NON esattamente divisibile per p (core)
//in modo tale da poter essere generalizzato

//Utilizzo della 2a strategia (reduction)

/**
 * In questa strategia, utilizziamo la clausola 'reduction' con la variabile
 * condivisa 'sum' e l'operatore '+' per indicare che ogni thread calcola
 * la sua somma parziale e la aggiunge in modo sicuro alla variabile condivisa 'sum'.
 * 
 * La clausola 'reduction(+:sum)' specifica che 'sum' è una variabile di riduzione 
 * e che l'operatore '+' deve essere utilizzato per aggregare correttamente i valori parziali tra i thread.
 * 
 * Questo approccio garantisce che i calcoli paralleli siano eseguiti in modo corretto
 * e sicuro, con OpenMP che si occupa internamente della sincronizzazione e dell'aggregazione
 * dei valori parziali tra i thread.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char**argv) {
    
    int N, i, nloc, t, indice, r, id, step;
    float *a, sum;
    //float sumtot = 0 -> diff con la 1a strategia

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
    #pragma omp parallel private(nloc, id, step, i) shared(a, N, r) reduction(+:sum)
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
        
        //AGGIORNAMENTO SOMMA GLOBALE PER LA 1a STRATEGIA, CON LA REDUCTION NON SI FA
        //sumtot += sum;
    }

    //STAMPA
    printf("somma finale: %f\n", sum);

    return 0;
}