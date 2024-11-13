/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:21:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/13 18:51:01 by ahamuyel         ###   ########.fr       */
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

	philo = (t_philosopher *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!philo_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (pointer);
}

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	watcher;
	int			i;

	if (pthread_create(&watcher, NULL, &monitor, program->philos))
		destory_all("failed to create philos", program, forks);
	i = 0;
	while (i < program->philos[0].number_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine,
				&program->philos[i]))
			destory_all("failed to create philos", program, forks);
		i++;
	}
	i = 0;
	while (i < program->philos[0].number_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
			destory_all("failed to join philos", program, forks);
		i++;
	}
	return (0);
}
