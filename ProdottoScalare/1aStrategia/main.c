//prodotto scalare tra due vettori

//1a strategia

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char**argv) {
    
    int N, i, nloc, t, indice;
    int *a, *b, *c;
    int sum, sumtot = 0;

    printf("Inserisci dimensione N dei vettori: ");
    scanf("%d", &N);

    srand(time(NULL));
    
    //allocazione vettori input (a, b) e output(c)
    a = (int*)calloc(N, sizeof(int));
    b = (int*)calloc(N, sizeof(int));
    c = (int*)calloc(N, sizeof(int));

    //inizializzazione e stampa
    for(i = 0; i < N; i++ )
        a[i] = rand() % 10 + 1;
    printf("Vettore A: \n");
    for(i = 0; i < N; i++)
        printf(" %d  ", a[i]);
    printf("\n");

    //inizializzazione e stampa
    for(i = 0; i < N; i++ )
        b[i] = rand() % 10 + 1;
    printf("Vettore B: \n");
    for(i = 0; i < N; i++)
        printf(" %d  ", b[i]);
    printf("\n");

    #pragma omp parallel for private (i) shared(a, b, c, N) schedule(static)
    for(i = 0; i < N; i++)
    {
        c[i] = a[i]*b[i];
    }

    printf("Vettore Risultato C: \n");
    for(i = 0; i < N; i++)
        printf(" %d  ", c[i]);
    printf("\n"); 

    sum = 0;
    #pragma omp parallel for private(i, sum) shared(sumtot) schedule(static)
    for(i = 0; i < N; i++)
    {
        sum = c[i];
        #pragma omp atomic
        sumtot += sum;
    }

    //Stampa Prodotto Scalare
	printf( "Somma Totale: %d\n", sumtot );

    //buona norma è liberare la memoria
	free(a);
	free(b);
	free(c);

    return 0;
}