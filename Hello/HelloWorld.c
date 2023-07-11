//HelloWorld #pragma omp

#include <omp.h>
#include <stdio.h>

//omp_get_thread_num() return id thread
//omp_get_num_threads() return num thread attivi

int main() 
{
    //Creazione di un team di thread
    #pragma omp parallel
    printf( "Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads() );

    return 0;
}