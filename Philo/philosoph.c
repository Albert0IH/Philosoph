#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5
#define EAT_TIME 2
#define SLEEP_TIME 3

pthread_mutex_t forks[NUM_PHILOSOPHERS]; // Garfos (mutexes)
pthread_mutex_t print_mutex;             // Mutex para controle da saída

// Função para o filósofo comer
void *philosopher(void *arg)
{
    int id = *((int *)arg);
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (1)
    {
        // Pensar
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Pegar os garfos
        if (id % 2 == 0)
        {
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        }
        else
        {
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }

        // Comer
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is eating.\n", id);
        pthread_mutex_unlock(&print_mutex);
        sleep(EAT_TIME);

        // Deixar os garfos
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);

        // Dormir
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is sleeping.\n", id);
        pthread_mutex_unlock(&print_mutex);
        sleep(SLEEP_TIME);
    }

    return NULL;
}

int main(void)
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    
    // Inicializar os mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }
    pthread_mutex_init(&print_mutex, NULL);

    // Criar as threads dos filósofos
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosopher_ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]))
        {
            perror("Failed to create philosopher thread");
            return 1;
        }
    }

    // Esperar as threads terminarem (não terminam, pois o loop é infinito)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destruir os mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_mutex);

    return 0;
}
