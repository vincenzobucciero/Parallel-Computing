#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int idThread, num_thread;
    

    /*
        Le variabili SHARED sono condivise tra tutti i thread all'interno di una regione parallela.
        Quando una variabile è dichiarata come shared, ogni thread può accedere e modificare la stessa 
        posizione di memoria che rappresenta quella variabile. 
        Eventuali modifiche apportate da un thread saranno visibili a tutti gli altri thread.
        Possibile race condition ma qui è sicuro che non ci siano poichè i thread non effettuano nessuna 
        operazione di scrittura ma solo lettura.
    */

    /*
        Le variabili PRIVATE, invece, sono uniche per ogni thread. Ogni thread ha una copia privata 
        della variabile e le modifiche apportate da un thread non influiscono sul valore della 
        variabile negli altri thread.
    */
    #pragma omp parallel private(idThread) shared(num_thread)   //definizione di variabili private/shared
    {
        //restituisce il numero del thread corrente all'interno di una regione parallela. 
        //Ogni thread ha un numero univoco che rappresenta la sua identità.
        idThread = omp_get_thread_num();

        //restituisce il numero totale di thread che partecipano all'esecuzione di una regione parallela. 
        num_thread = omp_get_num_threads();

        printf("Hello from thread %d, num_thread %d\n", idThread, num_thread);
    }
    
    return 0;
}