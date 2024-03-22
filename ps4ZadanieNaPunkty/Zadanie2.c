#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10

int iterations_per_thread[NUM_THREADS];
int all_iterations=0;
void* thread_function(void* arg) {
    int thread_id = *((int*)arg);
    int iterations = rand() % 10001;
    
    for (int i = 0; i < iterations; i++) {
        printf("Wątek %d iteracja %d\n", thread_id, i);
        //flush(stdout);
        //usleep(1000000); // Opóźnienie 100ms
    }
    iterations_per_thread[thread_id] = iterations;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    srand(time(NULL));
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        
    }
    int all_iterations=0;
    for (int i = 0; i < NUM_THREADS; i++) {
        all_iterations+=iterations_per_thread[i];
    }
    
    printf("Łączna liczba iteracji: %d\n", all_iterations);
    
    
}