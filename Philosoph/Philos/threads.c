/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:21:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/13 14:10:59 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *pointer)
{
	int				i;
	t_philosopher	*philo;
	pthread_mutex_t	mutex;

	philo = (t_philosopher *)pointer;
	i = 0;
	while (i < 1)
	{
		pthread_mutex_lock(&mutex);
		printf("philo [%d]\n", philo->id);
		pthread_mutex_unlock(&mutex);
		i++;
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
		if (pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]))
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
