/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:25:02 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 19:14:04 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *s, t_philosoph *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_current_time() - philo->start_time;
	if (!check_dead(philo))
		printf("%zu %d %s\n", time, id, s);
	pthread_mutex_unlock(philo->print_lock);
}

int	philos_dead(t_philosoph *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal > time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	search_death(t_philosoph *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].number_of_philos)
	{
		if (philos_dead(&philos[i], philos[i].time_to_die))
		{
			print_msg("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[i].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philosoph *philos)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philos[0].number_times_to_eat == -1)
		return (0);
	while (i < philos[0].number_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten > philos[i].number_times_to_eat)
			finished++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished == philos[0].number_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philosoph *philos;
	philos = (t_philosoph *)arg;
	while (1)
		if (search_death(philos) || check_if_all_ate(philos))
			break ;
	return (arg);
}