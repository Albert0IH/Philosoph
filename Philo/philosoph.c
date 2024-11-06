#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_PHILOSOPHERS 5
#define EAT_TIME 2
#define SLEEP_TIME 3
#define MAX_TIME_WITHOUT_EATING 10 // Tempo máximo sem comer antes de "morrer"

typedef struct s_philosopher
{
    int id;
    pthread_t thread;
    long last_meal_time; // Armazena o tempo do último prato
    pthread_mutex_t *forks; // Ponteiro para os mutexes dos garfos
    pthread_mutex_t *print_mutex; // Ponteiro para o mutex de impressão
    int *simulation_active; // Sinal para controle da simulação
} t_philosopher;

// Função para obter o tempo atual em milissegundos
long get_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// Função para o filósofo executar suas ações
void *philosopher(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    int left = philo->id;
    int right = (philo->id + 1) % NUM_PHILOSOPHERS;

    while (*philo->simulation_active)  // Verifica se a simulação está ativa
    {
        // Pensar
        pthread_mutex_lock(philo->print_mutex);
        if (!*philo->simulation_active) // Verifica a simulação novamente após o lock
        {
            pthread_mutex_unlock(philo->print_mutex);
            break;
        }
        printf("Philosopher %d is thinking.\n", philo->id);
        pthread_mutex_unlock(philo->print_mutex);
        sleep(1);

        // Pegar os garfos
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(&philo->forks[left]);
            pthread_mutex_lock(&philo->forks[right]);
        }
        else
        {
            pthread_mutex_lock(&philo->forks[right]);
            pthread_mutex_lock(&philo->forks[left]);
        }

        // Comer
        pthread_mutex_lock(philo->print_mutex);
        if (!*philo->simulation_active)
        {
            pthread_mutex_unlock(philo->print_mutex);
            pthread_mutex_unlock(&philo->forks[left]);
            pthread_mutex_unlock(&philo->forks[right]);
            break;
        }
        printf("Philosopher %d is eating.\n", philo->id);
        pthread_mutex_unlock(philo->print_mutex);
        philo->last_meal_time = get_time_ms(); // Atualiza o tempo da última refeição
        sleep(EAT_TIME);

        // Deixar os garfos
        pthread_mutex_unlock(&philo->forks[right]);
        pthread_mutex_unlock(&philo->forks[left]);

        // Dormir
        pthread_mutex_lock(philo->print_mutex);
        if (!*philo->simulation_active)
        {
            pthread_mutex_unlock(philo->print_mutex);
            break;
        }
        printf("Philosopher %d is sleeping.\n", philo->id);
        pthread_mutex_unlock(philo->print_mutex);
        sleep(SLEEP_TIME);

        // Verificar se o filósofo morreu
        pthread_mutex_lock(philo->print_mutex);
        if (get_time_ms() - philo->last_meal_time > MAX_TIME_WITHOUT_EATING && *philo->simulation_active)
        {
            printf("Philosopher %d has died due to starvation.\n", philo->id);
            *philo->simulation_active = 0; // Encerra a simulação
        }
        pthread_mutex_unlock(philo->print_mutex);

        if (!*philo->simulation_active)
            break;
    }

    return NULL;
}

int main(void)
{
    pthread_mutex_t forks[NUM_PHILOSOPHERS]; // Garfos (mutexes)
    pthread_mutex_t print_mutex;             // Mutex para controle da saída
    int simulation_active = 1;               // Flag de controle da simulação
    t_philosopher philosophers[NUM_PHILOSOPHERS];

    // Inicializar os mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
        philosophers[i].id = i;
        philosophers[i].last_meal_time = get_time_ms(); // Iniciar o tempo com o tempo atual
        philosophers[i].forks = forks;
        philosophers[i].print_mutex = &print_mutex;
        philosophers[i].simulation_active = &simulation_active;
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

    // Esperar as threads terminarem
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
