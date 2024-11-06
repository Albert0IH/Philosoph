/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 03:47:45 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/06 07:37:16 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOS 15
#define EAT_TIME 1
#define SLEEP_TIME 3

pthread_mutex_t	forks[NUM_PHILOS];
pthread_mutex_t	print_mutex;

void	*philo(void *arg)
{
	int	id;
	int	left;
	int	right;

	id = *((int *)arg);
	left = id;
	right = (id + 1) % NUM_PHILOS;

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
	return (NULL);
}

int	main(void)
{
	pthread_t	philos[NUM_PHILOS];
	int			philo_ids[NUM_PHILOS];
	int			i;

	i = 0;
	// INIT MUTEXES
	while (i < NUM_PHILOS)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
    pthread_mutex_init(&print_mutex, NULL);
	i = 0;
	// CREATE PHILOS
	while (i < NUM_PHILOS)
	{
        philo_ids[i] = i;
		if (pthread_create(&philos[i], NULL, philo, &philo_ids[i]))
		{
			perror("Failed to create philosoph");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < NUM_PHILOS)
	{
		if (pthread_join(philos[i], NULL))
		{
			perror("Failed to join philosoph");
			return (1);
		}
        i++;
	}
	i = 0;
	while (i < NUM_PHILOS)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&print_mutex);
	return (0);
}
