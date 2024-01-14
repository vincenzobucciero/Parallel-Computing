//algortimo somma tra due vettori di dimensione N

// -> Algoritmo full parallel

// N dimensione NON esattamente divisibile per p (num core)

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char**argv) {
    
    int N, i, nloc, t, indice, r, id, step;
    float *a, *b, *c;

    printf("Inserisci dimensione N dei vettori: ");
    scanf("%d", &N);

    srand(time(NULL));
    
    //allocazione vettori input (a, b) e output(c)
    a = (float*)calloc(N, sizeof(float));
    b = (float*)calloc(N, sizeof(float));
    c = (float*)calloc(N, sizeof(float));

    //inizializzazione e stampa
    for(i = 0; i < N; i++ )
        a[i] = rand() % 100 + 1;
    printf("Vettore A: \n");
    for(i = 0; i < N; i++)
        printf(" %f  ", a[i]);
    printf("\n");

    //inizializzazione e stampa
    for(i = 0; i < N; i++ )
        b[i] = rand() % 100 + 1;
    printf("Vettore B: \n");
    for(i = 0; i < N; i++)
        printf(" %f  ", b[i]);
    printf("\n");

    //Inizia una regione parallela con le variabili i, indice, e nloc come variabili private (una copia per ogni thread)
    //e condividendo i vettori a, b, e c tra tutti i thread.
    #pragma omp parallel private(i, indice, nloc, id, step) shared(a, b, c, r)
    {
        //numero totale di thread nella regione parallela
        t = omp_get_num_threads();
        //dimensione locale (nloc) per ciascun thread in base alla dimensione totale N e al numero di thread t
        nloc = N/t;
        //resto della divisione
        r = N % t;
        //identificatore del thread corrente
        id = omp_get_thread_num();

        //suddivisione del lavoro tra i thread
		if(id < r)
		{
			nloc++;
			step = 0;
		}
		else
			step = r;

        //Inizia un ciclo for per ogni thread, limitato alla sua porzione di dati
        for(i = 0; i < nloc; i++)
        {
            //Calcola l'indice globale corrispondente all'elemento attualmente processato dal thread
            indice = i + nloc * omp_get_thread_num() + step;
            //addizione vettoriale sugli elementi corrispondenti dei vettori a e b, assegnando il risultato al vettore c
            c[indice] = a[indice] + b[indice];
        }
    }

    printf("Vettore C: \n");
    for(i = 0; i < N; i++)
        printf(" %f  ", c[i]);
    printf("\n");

    return 0;
}