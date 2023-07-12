//Esercizio calcolo piGreco

/**
 *  Tra tutti i modi per calcolare il numero π, si può considerare il seguente
    integrale:

                integrale tra 0 e 1 di 4 / (1 + x^2) in dx = π

    for (i = 1; i <= n; i++)
    {
        x = dx * ((double) (i - 0.5));
        f = 4.0 / (1.0 + x*x);
        sum = sum + f;
    }
*/

//2a STRATEGIA

#include <stdio.h>
#include <omp.h>

#define N 100000000

int main() {
    double dx, x, f, sum, pi;
    long int i, n = N;

    printf("numero di intervalli: %ld\n", n);
    sum = 0.0;

    dx = 1.0 / (double)n;

    /**
     *  Bisogna stare attenti solo a quali variabili sono shared e
     *  quali private.
     *  Combinando il costrutto parallel con il costrutto for tutte
     *  le istruzione da fare devono essere comprese tra le
     *  parentesi del for interno
    */
    #pragma omp parallel for private(x, f, i) shared(dx, n) reduction(+:sum)
    for ( i = 1; i <= n; i++)
    {
        x = dx * ((double) (i - 0.5));
        f = 4.0 / (1.0 + x*x);

        sum = sum + f;
    }

    pi = dx*sum;
    
    printf("PI %.24f\n", pi);
    
    return 0;
    
}