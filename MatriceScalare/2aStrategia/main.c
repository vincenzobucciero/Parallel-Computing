//Prodotto di una Matrice x uno Scalare

//Utilizzo della 2a Strategia -> SUDDIVISIONE PER BLOCCHI COLONNA

//ylenia ti amo

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char**argv) {
    int N, M, **matrix, scalare;
    double t1, t2, t_tot;

    printf("Inserisci numero RIGHE della matrice: ");
    scanf("%d", &N);
    printf("Inserisci numero COLONNE della matrice: ");
    scanf("%d", &M);

    srand(time(NULL));

    //allocazione dinamica della matrice x righe
    matrix = (int**)calloc(N, sizeof(int*));
    for(size_t i = 0; i < N; i++) {
        matrix[i] = (int*)calloc(M,sizeof(int));
    }

    //Inizializzazione e riempimento della matrice con valori casuali
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            matrix[i][j] = rand()%10+1;
        }
    }

    //stampa matrice
    printf("MATRICE A: \n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    //Inserimento dello SCALARE che moltiplica
    printf("Inserisci lo SCALARE da moltiplicare: ");
    scanf("%d", &scalare);

    t1 = omp_get_wtime();

    //RISPETTO ALLA PRIMA STRATEGIA (SUDDIVISIONE PER BLOCCHI RIGHE), QUI SI DIVIDE LA MATRICE
    //PER BLOCCHI COLONNE, QUINDI SI INVERTE IL CICLO FOR
    #pragma omp parallel for shared(N, M, matrix) schedule(guided)
    for(int j = 0; j < M; j++)
    {
        for(int i = 0; i < N; i++) 
        {
            matrix[i][j] *= scalare;
        }
    }

    t2 = omp_get_wtime();

    t_tot = t2-t1;

    //stampa della matrice finale
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("TEMPO t1 INIZIALE : %lf\n", t1);
    printf("TEMPO t2 FINALE : %lf\n", t2);
    printf("TEMPO TOTALE t_tot [FINALE-INIZIALE]: %lf\n", t_tot);

    return 0;
}
// ylenia sei la mia vita ti amo sei bellissima stupenda fantasticaaa 