#include <stdio.h>
#include <pthread.h>

int Licznik = 0;

void* Watek1(void* arg) {
    while (1) {
        printf("Wartosc Licznika: %d\n", Licznik);
    }
    return NULL;
}

void* Watek2(void* arg) {
    while (1) {
        Licznik++;
    }
    return NULL;
}

int main() {
    pthread_t watek1, watek2;
    
    pthread_create(&watek1, NULL, Watek1, NULL);
    pthread_create(&watek2, NULL, Watek2, NULL);
    
    pthread_join(watek1, NULL);
    pthread_join(watek2, NULL);
    
    return 0;
}