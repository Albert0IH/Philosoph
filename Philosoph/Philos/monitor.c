/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:50:41 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/13 18:38:21 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *s, t_philosopher *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_current_time() - philo->start_time;
	if (!philo_dead(philo))
		printf("%zu %d %s\n", time, id, s);
	pthread_mutex_unlock(philo->print_lock);
}

int	kill_philo(t_philosopher *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_death(t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].number_of_philos)
	{
		if (kill_philo(&philos[i], philos[i].time_to_die))
		{
			print_msg("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philosopher *philos;
	philos = (t_philosopher *)pointer;
	while (1)
	{
		if (check_death(philos))
			break ;
	}
	return (pointer);
}