/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:54:47 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/13 19:01:09 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philosoph *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philos_rotine(void *arg)
{
	t_philosoph	*philo;

	philo = (t_philosoph *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!philo_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (arg);
}

int	create_thread(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	watcher;
	int			i;

	if (pthread_create(&watcher, NULL, &monitor, program->philos))
		destory_all("Failed to create watche'r thread", program, forks);
	i = 0;
	while (i < program->philos[0].number_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philos_rotine,
				&program->philos[i]))
			destory_all("Failed to create philo's thread", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(watcher, NULL))
		destory_all("Failed to join watcher's thread", program, forks);
	while (i < program->philos[0].number_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
			destory_all("Failed to join philo's thread", program, forks);
		i++;
	}
	return (0);
}
