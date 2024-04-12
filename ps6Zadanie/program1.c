#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t forks[5];
void* philosopher0Handler(void *parameter)
{
    // Aktualny wątek - filozof o numerze index
    int index = *(int*)parameter;
    int rightIndex = (index + 1) % 5;
    // Inicjujemy generator liczb pseudolosowych w aktualnym wątku.
    srand(time(NULL));
    while (1)
    {
        // Zakładamy blokadę na prawy widelec aktualnego. Jeżeli jego prawy sąsiad akurat ma podniesiony ten widelec, czyli je nim lub czeka na zwolnienie swojego prawego widelca, to aktualny przechodzi w stan oczekujący.
        // if (pthread_mutex_lock(&forks[rightIndex]) == 0) // z obsługą błędów funkcji
        pthread_mutex_lock(&forks[rightIndex]);
        printf("%i podniosl prawy widelec (%i) i wciaz mysli\n", index, rightIndex);
        // Zakładamy blokadę na lewy widelec aktualnego. Jeżeli jego lewy sąsiad akurat je tym widelcem, to aktualny przechodzi w stan oczekujący (uśpienia).
        pthread_mutex_lock(&forks[index]);
        printf("%i podniosl lewy widelec (%i), konczy myslec i zaczyna jesc\n", index, index);
        int sleepTime = rand() % 1000;
        usleep(sleepTime);
        printf("%i konczy jesc i zaczyna myslec\n", index);
        // Zwalniamy blokadę prawego widelca aktualnego.
        pthread_mutex_unlock(&forks[rightIndex]);
        printf("%i polozyl prawy widelec (%i) i wciaz mysli\n", index, rightIndex);
        // Zwalniamy blokadę lewego widelca aktualnego.
        pthread_mutex_unlock(&forks[index]);
        printf("%i polozyl lewy widelec (%i) i wciaz mysli\n", index, index);
    }
    return NULL; // równoważne pthread_exit(NULL);
}

void* philosopherHandler(void *parameter)
{
    // Aktualny wątek - filozof o numerze index
    int index = *(int*)parameter;
    int rightIndex = (index + 1) % 5;
    // Inicjujemy generator liczb pseudolosowych w aktualnym wątku.
    srand(time(NULL));
    while (1)
    {
        // Zakładamy blokadę na lewy widelec aktualnego. Jeżeli jego lewy sąsiad akurat je tym widelcem, to aktualny przechodzi w stan oczekujący (uśpienia).
        // if (pthread_mutex_lock(&forks[index]) == 0) // z obsługą błędów funkcji
        pthread_mutex_lock(&forks[index]);
        printf("%i podniosl lewy widelec (%i) i wciaz mysli\n", index, index);
        // Zakładamy blokadę na prawy widelec aktualnego. Jeżeli jego prawy sąsiad akurat ma podniesiony ten widelec, czyli je nim lub czeka na zwolnienie swojego prawego widelca, to aktualny przechodzi w stan oczekujący.
        pthread_mutex_lock(&forks[rightIndex]);
        printf("%i podniosl prawy widelec (%i), konczy myslec i zaczyna jesc\n", index, rightIndex);
        int sleepTime = rand() % 1000;
        usleep(sleepTime);
        printf("%i konczy jesc i zaczyna myslec\n", index);
        // Zwalniamy blokadę lewego widelca aktualnego.
        pthread_mutex_unlock(&forks[index]);
        printf("%i polozyl lewy widelec (%i) i wciaz mysli\n", index, index);
        // Zwalniamy blokadę prawego widelca aktualnego.
        pthread_mutex_unlock(&forks[rightIndex]);
        printf("%i polozyl prawy widelec (%i) i wciaz mysli\n", index, rightIndex);
    }
    return NULL; // równoważne pthread_exit(NULL);
}

int main()
{
    pthread_t threads[5];
    int i = 0;
    pthread_create(&threads[i], NULL, philosopher0Handler, &i);
    for (i = 1; i <  5; ++i)
        pthread_create(&threads[i], NULL, philosopherHandler, &i);
    for (i = 0; i <  5; ++i)
        pthread_join(threads[i], NULL);
    return 0;
}