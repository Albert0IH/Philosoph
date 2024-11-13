/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:21:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/13 17:39:43 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *pointer)
{
	t_philosopher	*philo;
	pthread_mutex_t	mutex;

	philo = (t_philosopher *)pointer;
	// pthread_mutex_lock(&mutex);
	// printf("philo [%d]\n", philo->id);
	// pthread_mutex_unlock(&mutex);
	while (!philo_dead(philo))
	{
		pthread_mutex_lock(&mutex);
		printf("philo [%d]\n", philo->id);
		pthread_mutex_unlock(&mutex);
		// eat
		// esleep
		// think
	}
	return (pointer);
}

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_init(forks, NULL);
	i = 0;
	while (i < program->philos[0].number_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine,
				&program->philos[i]))
			printf("Failed to create Philo [%d]", program->philos[i].id);
		i++;
	}
	i = 0;
	while (i < program->philos[0].number_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
			printf("Failed to join Philo [%d]", program->philos[i].id);
		i++;
	}
	pthread_mutex_destroy(forks);
	return (0);
}
