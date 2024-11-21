/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:13:52 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/21 10:42:01 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosoph *philo)
{
	if (philo->number_of_philos == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	if (philo->number_of_philos % 2 != 0)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	print_msg("has taken a fork", philo, philo->id);
	print_msg("has taken a fork", philo, philo->id);
}

void	thinking(t_philosoph *philo)
{
	print_msg("is thinking", philo, philo->id);
}

void	sleeping(t_philosoph *philo)
{
	print_msg("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep, philo);
}

void	eating(t_philosoph *philo)
{
	philo->eating = 1;
	print_msg("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	error_msg(char *msg)
{
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}
