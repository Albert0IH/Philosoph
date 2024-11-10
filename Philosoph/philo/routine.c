/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:13:52 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 19:13:56 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philosoph *philo)
{
	print_msg("is thinking", philo, philo->id);
}

void	sleeping(t_philosoph *philo)
{
	print_msg("is spleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void eating(t_philosoph *philo)
{
    pthread_mutex_lock(philo->r_forks);
    print_msg("has taken a fork", philo, philo->id);
    if (philo->number_of_philos == 1)
    {
        ft_usleep(philo->time_to_die);
        pthread_mutex_unlock(philo->r_forks);
        return ;
    }
    pthread_mutex_lock(philo->l_forks);
    print_msg("has taken a fork", philo, philo->id);
    philo->eating = 1;
    print_msg("is eating", philo, philo->id);
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_to_eat);
    philo->eating = 0;
    pthread_mutex_lock(philo->l_forks);
    pthread_mutex_lock(philo->r_forks);
}
