/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:50:40 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/14 12:51:21 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_input(t_philosoph *philos, char **av)
{
	philos->number_of_philos = ft_atoi(av[1]);
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philos->number_times_to_eat = ft_atoi(av[5]);
	else
		philos->number_times_to_eat = -1;
}

void	set_philos(t_philosoph *philos, t_program *program,
		pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		take_input(&philos[i], av);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].number_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philos_number)
{
	int	i;

	i = 0;
	while (i < philos_number)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philosoph *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
