/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 06:51:41 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/08 11:30:13 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 100 + tv.tv_usec / 1000);
}

void take_forks(t_philo *philo, int left, int right, long start_time)
{
    long time = get_time_ms() - start_time;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->forks[left]);
        printf("%ld %d took his left's fork.\n", time, philo->id);
        pthread_mutex_lock(&philo->forks[right]);
        printf("%ld %d took his right's fork.\n", time, philo->id);
    }
    else
    {
        pthread_mutex_lock(&philo->forks[right]);
        printf("%ld %d took his right's fork.\n", time, philo->id);
        pthread_mutex_lock(&philo->forks[left]);
        printf("%ld %d took his left's fork.\n", time, philo->id);
    }
}

void philo_eat_sleep_think(t_philo *philo, int left, int right, long start_time)
{
    long time = get_time_ms() - start_time;
    pthread_mutex_lock(philo->print_mutex);
    if (*philo->simulation_active)
        printf("%ld %d is eating.\n", time, philo->id);
    pthread_mutex_unlock(philo->print_mutex);

    philo->last_meal_time = get_time_ms();
    sleep(EAT_TIME);
    pthread_mutex_unlock(&philo->forks[left]);
    pthread_mutex_unlock(&philo->forks[right]);

    pthread_mutex_lock(philo->print_mutex);
    if (*philo->simulation_active)
        printf("%ld %d is sleeping.\n", get_time_ms() - start_time, philo->id);
    pthread_mutex_unlock(philo->print_mutex);
    sleep(SLEEP_TIME);

    pthread_mutex_lock(philo->print_mutex);
    if (*philo->simulation_active)
        printf("%ld %d is thinking.\n", get_time_ms() - start_time, philo->id);
    pthread_mutex_unlock(philo->print_mutex);
    sleep(1);
}

void *philo(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int left = philo->id;
    int right = (philo->id + 1) % NUM_PHILOS;
    long start_time = get_time_ms();

    while (*philo->simulation_active)
    {
        take_forks(philo, left, right, start_time);
        philo_eat_sleep_think(philo, left, right, start_time);

        // Verifica se o filósofo morreu
        if (get_time_ms() - philo->last_meal_time > MAX_TIME_WITHOUT_EATING)
        {
            pthread_mutex_lock(philo->print_mutex);
            if (*philo->simulation_active)
            {
                printf("%ld %d has died.\n", get_time_ms() - start_time, philo->id);
                *philo->simulation_active = 0;
            }
            pthread_mutex_unlock(philo->print_mutex);
            break; // Sai do loop ao detectar a morte
        }
    }
    return NULL;
}

void initialize_mutexes(pthread_mutex_t *forks, pthread_mutex_t *print_mutex)
{
    for (int i = 0; i < NUM_PHILOS; i++)
        pthread_mutex_init(&forks[i], NULL);
    pthread_mutex_init(print_mutex, NULL);
}

void initialize_philos(t_philo *philos, pthread_mutex_t *forks, pthread_mutex_t *print_mutex, int *simulation_active)
{
    for (int i = 0; i < NUM_PHILOS; i++)
    {
        philos[i].id = i + 1;
        philos[i].forks = forks;
        philos[i].last_meal_time = get_time_ms();
        philos[i].print_mutex = print_mutex;
        philos[i].simulation_active = simulation_active;
    }
}

void create_philos_threads(t_philo *philos)
{
    for (int i = 0; i < NUM_PHILOS; i++)
    {
        if (pthread_create(&philos[i].thread, NULL, philo, &philos[i]))
        {
            perror("Failed to create philosopher");
            exit(1);
        }
    }
}

void destroy_mutexes(pthread_mutex_t *forks, pthread_mutex_t *print_mutex)
{
    for (int i = 0; i < NUM_PHILOS; i++)
        pthread_mutex_destroy(&forks[i]);
    pthread_mutex_destroy(print_mutex);
}

int main(void)
{
    pthread_mutex_t forks[NUM_PHILOS];
    pthread_mutex_t print_mutex;
    int simulation_active = 1;
    t_philo philos[NUM_PHILOS];

    initialize_mutexes(forks, &print_mutex);
    initialize_philos(philos, forks, &print_mutex, &simulation_active);
    create_philos_threads(philos);

    for (int i = 0; i < NUM_PHILOS; i++)
        pthread_join(philos[i].thread, NULL);

    destroy_mutexes(forks, &print_mutex);
    return (0);
}
