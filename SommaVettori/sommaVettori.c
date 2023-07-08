//Somma tra vettori - algoritmo N = k*p

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main()
{
    int i, nloc, indice, t;
    float *a, *b, *c;
    int N;

    printf("Inserisci dimensione N:  ");
    scanf(" %d", &N);

    a = (float*)calloc(N, sizeof(float));
    b = (float*)calloc(N, sizeof(float));
    c = (float*)calloc(N, sizeof(float));

    printf("Inserire gli elementi del vettore a\n");
    for (i=0;i<N;i++)
    {
        scanf("%f",&a[i]);
    }

    printf("Inserire gli elementi del vettore b\n");
    for (i=0;i<N;i++)
    {
        scanf("%f",&b[i]);
    }

    printf("Vettore A: \n");
    for (i=0;i<N;i++)
    {
        printf("%f  ",a[i]);
    }

    printf("\n\n");
    printf("Vettore B: \n");
    for (i=0;i<N;i++)
    {
        printf("%f  ",b[i]);
    }

    #pragma omp parallel private(nloc, i, indice) shared(a, b, c)
    {
        t = omp_get_num_threads();
        nloc = N / t;
        
    }

    return 0;
}