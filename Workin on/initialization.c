/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:50:40 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/20 13:41:15 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_input(t_philosoph *philo, char **input)
{
    philo->number_of_philos = ft_atoi(input[1]);
    philo->time_to_die = ft_atoi(input[2]);
    philo->time_to_eat = ft_atoi(input[3]);
    philo->time_to_sleep = ft_atoi(input[4]);
    if (input[5])
        philo->number_of_meals = ft_atoi(input[5]);
    else
        philo->number_of_meals = -1;
}
