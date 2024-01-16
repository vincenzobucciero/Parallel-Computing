//Prodotto di una Matrice x uno Scalare

//Utilizzo della 3a Strategia -> SUDDIVISIONE PER BLOCCHI RIGA + COLONNA

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char**argv) {
    int N, M, *matrix, scalare;
    double t1, t2, t_tot;
    int numThreads = 4;
    int Np = (N/(numThreads/2));
    int Mp = (M/(numThreads/2));

    printf("Inserisci numero RIGHE della matrice: ");
    scanf("%d", &N);
    printf("Inserisci numero COLONNE della matrice: ");
    scanf("%d", &M);

    srand(time(NULL));

    //allocazione dinamica della matrice
    matrix = (int*)calloc(N*M, sizeof(int*));

    //Inizializzazione e riempimento della matrice con valori casuali
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            matrix[(i * N) + j] = rand()%10+1;
        }
    }

    //stampa matrice
    printf("MATRICE A: \n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            printf("%d\t", matrix[(i * N) + j]);
        }
        printf("\n");
    }

    //Inserimento dello SCALARE che moltiplica
    printf("Inserisci lo SCALARE da moltiplicare: ");
    scanf("%d", &scalare);

    t1 = omp_get_wtime();

    //RISPETTO ALLA PRIMA/SECONDA STRATEGIA (SUDDIVISIONE PER BLOCCHI RIGA/COLONNA), QUI SI DIVIDE LA MATRICE
    //PER BLOCCHI RIGA + COLONNA
    #pragma omp parallel num_threads(numThreads) shared(matrix)
    {
        int threadID = omp_get_thread_num();
        int rowStart = (threadID/2)*Np;
        int colStart = (threadID%2)*Mp;

        for(int i = rowStart; i < rowStart+Np; i++)
        {
            for(int j = colStart; j < colStart+Mp; j++) 
            {
                matrix[i * M + j] = threadID;
            }
        }
    }

    t2 = omp_get_wtime();

    t_tot = t2-t1;

    //stampa della matrice finale
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            printf("%d\t", matrix[(i * N) + j]);
        }
        printf("\n");
    }

    printf("TEMPO t1 INIZIALE : %lf\n", t1);
    printf("TEMPO t2 FINALE : %lf\n", t2);
    printf("TEMPO TOTALE t_tot [FINALE-INIZIALE]: %lf\n", t_tot);

    return 0;
}
// ylenia sei la mia vita ti amo sei bellissima stupenda fantasticaaa 