/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:42:03 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/13 18:08:08 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thinking(t_philosopher *philo)
{
    print_msg("is thinking", philo, philo->id);
}

void sleeping(t_philosopher *philo)
{
    print_msg("is sleeping", philo, philo->id);
    ft_usleep(philo->time_to_sleep);
}

void eating(t_philosopher *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_msg("has taken a fork", philo, philo->id);
    if (philo->number_of_philos == 1)
    {
        ft_usleep(philo->time_to_die);
        pthread_mutex_unlock(philo->r_fork);
        return ;
    }
    pthread_mutex_lock(philo->l_fork);
    print_msg("has taken a fork", philo, philo->id);
    philo->eating = 1;
    print_msg("is eating", philo, philo->id);
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_to_die);
    philo->eating = 0;
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}