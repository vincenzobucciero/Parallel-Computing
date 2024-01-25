#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

int main(int argc, char**argv) {
    int **matrix, *x, *y;
    int N, M;
    int nloc = 0, step, resto, id, num_threads;

    srand(time(NULL));

    printf("Inserisci numero N di righe della matrice: ");
    scanf("%d", &N);
    printf("Inserisci numero M di colonne della matrice: ");
    scanf("%d", &M);

    matrix = (int**)calloc(N, sizeof(int*));
    for(size_t i = 0; i < N; i++) {
        matrix[i] = (int*)calloc(M, sizeof(int));
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            matrix[i][j] = rand()%10;
        }
    }
    printf("MATRICE A[%dx%d]: \n", N, M);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    x = (int*)calloc(M, sizeof(int));
    for(int i = 0; i < M; i++) {
        x[i] = rand()%10;
    }
    printf("VETTORE x DIMENSIONE [%d]: \n", M);
    for(int i = 0; i < M; i++) {
        printf("%d\t", x[i]);
    }
    printf("\n");

    y = (int*)calloc(N, sizeof(int));