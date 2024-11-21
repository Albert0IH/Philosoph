/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:54:47 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/21 10:32:30 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philosoph *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->death)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philos_rotine(void *arg)
{
	t_philosoph	*philo;

	philo = (t_philosoph *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (!philo_dead(philo))
	{
		take_forks(philo);
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
		destroy_all("Failed to create watche'r thread", program, forks);
	i = 0;
	while (i < program->philos[0].number_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philos_rotine,
				&program->philos[i]))
			destroy_all("Failed to create philo's thread", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(watcher, NULL))
		destroy_all("Failed to join watcher's thread", program, forks);
	while (i < program->philos[0].number_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
			destroy_all("Failed to join philo's thread", program, forks);
		i++;
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milissec, t_philosoph *philos)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milissec)
	{
		pthread_mutex_lock(philos->dead_lock);
		if (*philos->death)
		{
			pthread_mutex_unlock(philos->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philos->dead_lock);
		usleep(1000);
	}
	return (0);
}
