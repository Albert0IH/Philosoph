/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosoph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:13:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/08 13:04:07 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	initialize_mutexes(pthread_mutex_t *forks, pthread_mutex_t *print_mutex)
{
	int	i;

	i = 0;
	while (i < NUM_PHILOS)
		pthread_mutex_init(&forks[i++], NULL);
	pthread_mutex_init(print_mutex, NULL);
}

void	initialize_philos(t_philo *philo, pthread_mutex_t *forks,
		pthread_mutex_t *print_mutex, int *simulation_active)
{
	int	i;

	i = 0;
	while (i < NUM_PHILOS)
	{
		philo[i].id = i + 1;
		philo[i].forks = forks;
		philo[i].last_meal_time = get_time_ms();
		philo[i].print_mutex = print_mutex; // Adiciona o mutex de impressão
		philo[i].simulation_active = simulation_active;
		i++;
	}
}

void	create_philos_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < NUM_PHILOS)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]))
		{
			printf("Failed to create philosopher\n");
			exit(1);
		}
		i++;
	}
}

void	destroy_mutexes(pthread_mutex_t *forks, pthread_mutex_t *print_mutex)
{
	int	i;

	i = 0;
	while (i < NUM_PHILOS)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(print_mutex);
}
