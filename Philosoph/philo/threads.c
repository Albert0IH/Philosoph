/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:54:47 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 19:13:45 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philosoph *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_lock(philo->dead_lock), 1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philosoph	*philo;

	philo = (t_philosoph *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (arg);
}

int	create_thread(t_simulation *simulation, pthread_mutex_t *forks)
{
	pthread_t	watcher;
	int			i;

	if (pthread_create(&watcher, NULL, &monitor, simulation->philos))
		destroy_all("Failed to create thread", simulation, forks);
	i = 0;
	while (i < simulation->philos[0].number_of_philos)
	{
		if (pthread_create(&watcher, NULL, &philo_routine, simulation->philos))
			destroy_all("Failed to create thread", simulation, forks);
		i++;
	}
	i = 0;
	if (pthread_join(watcher, NULL))
		destroy_all("Failed to join thread", simulation, forks);
	while (i < simulation->philos[0].number_of_philos)
	{
		if (pthread_join(watcher, NULL))
			destroy_all("Failed to join thread", simulation, forks);
		i++;
	}
    return (0);
}
