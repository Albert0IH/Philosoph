#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_PHILOSOPHERS 5
#define EAT_TIME 2
#define SLEEP_TIME 3
#define MAX_TIME_WITHOUT_EATING 10 // Tempo máximo sem comer antes de "morrer"

pthread_mutex_t forks[NUM_PHILOSOPHERS]; // Garfos (mutexes)
pthread_mutex_t print_mutex;             // Mutex para controle da saída

// Estrutura para armazenar o estado de cada filósofo
typedef struct s_philosopher
{
    int id;
    pthread_t thread;
    long last_meal_time; // Armazena o tempo do último prato
} t_philosopher;

t_philosopher philosophers[NUM_PHILOSOPHERS];

long get_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// Função para o filósofo comer
void *philosopher(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    int left = philo->id;
    int right = (philo->id + 1) % NUM_PHILOSOPHERS;

    while (1)
    {
        // Pensar
        printf("Philosopher %d is thinking.\n", philo->id);
        sleep(1);

        // Pegar os garfos
        if (philo->id % 2 == 0)
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
        printf("Philosopher %d is eating.\n", philo->id);
        pthread_mutex_unlock(&print_mutex);
        philo->last_meal_time = get_time_ms(); // Atualiza o tempo da última refeição
        sleep(EAT_TIME);

        // Deixar os garfos
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);

        // Dormir
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is sleeping.\n", philo->id);
        pthread_mutex_unlock(&print_mutex);
        sleep(SLEEP_TIME);

        // Verificar se o filósofo morreu
        if (get_time_ms() - philo->last_meal_time > MAX_TIME_WITHOUT_EATING)
        {
            pthread_mutex_lock(&print_mutex);
            printf("Philosopher %d has died due to starvation.\n", philo->id);
            pthread_mutex_unlock(&print_mutex);
            exit(1); // Matar o programa imediatamente
        }
    }

    return NULL;
}

int main(void)
{
    // Inicializar os mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
        philosophers[i].id = i;
        philosophers[i].last_meal_time = get_time_ms(); // Iniciar o tempo com o tempo atual
    }
    pthread_mutex_init(&print_mutex, NULL);

    // Criar as threads dos filósofos
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        if (pthread_create(&philosophers[i].thread, NULL, philosopher, &philosophers[i]))
        {
            perror("Failed to create philosopher thread");
            return 1;
        }
    }

    // Esperar as threads terminarem (não terminam, pois o loop é infinito)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i].thread, NULL);
    }

    // Destruir os mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_mutex);

    return 0;
}
