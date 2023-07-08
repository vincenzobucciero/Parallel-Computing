//HelloWorld #pragma omp

#include <omp.h>
#include <stdio.h>

/*
int main() {
    #pragma omp parallel
    printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());

    return 0;
}
*/

//omp_get_thread_num() return id thread
//omp_get_num_threads() return num thread attivi

int main() 
{
    int id_thread, num_threads;

    #pragma omp parallel shared(num_threads) private(id_thread)
    {
        id_thread = omp_get_thread_num();
        num_threads = omp_get_num_threads();

        printf("Hello from thread %d, nthreads %d\n", id_thread, num_threads);
    }

    return 0;
}