/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:50:40 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 18:48:00 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_inputs(t_philosoph *philos, char **av)
{
	philos->number_of_philos = atoi(av[1]);
	philos->time_to_die = atoi(av[2]);
	philos->time_to_eat = atoi(av[3]);
	philos->time_to_sleep = atoi(av[4]);
	if (av[5])
		philos->number_times_to_eat = atoi(av[5]);
	else
		philos->number_times_to_eat = -1;
}

void	init_philos(t_philosoph *philos, t_simulation *simulation,
		pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		init_inputs(&philos[i], av);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].print_lock = &simulation->print_lock;
		philos[i].dead_lock = &simulation->dead_lock;
		philos[i].meal_lock = &simulation->meal_lock;
		philos[i].dead = &simulation->dead_flag;
		philos[i].l_forks = &forks[i];
		if (i == 0)
			philos[i].r_forks = &forks[philos[i].number_of_philos - 1];
		else
			philos[i].r_forks = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_number)
{
	int	i;

	i = 0;
    while (i < philo_number)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void	init_simulation(t_simulation *simulation, t_philosoph *philos)
{
	simulation->dead_flag = 0;
	simulation->philos = philos;
	pthread_mutex_init(&simulation->print_lock, NULL);
	pthread_mutex_init(&simulation->dead_lock, NULL);
	pthread_mutex_init(&simulation->meal_lock, NULL);
}
