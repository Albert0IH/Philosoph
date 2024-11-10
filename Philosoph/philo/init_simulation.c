/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:50:40 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 23:50:45 by ahamuyel         ###   ########.fr       */
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

// void	print_philos_info(t_philosoph *philos)
// {
// 	printf("Philo id: %d\n", philos->id);
// 	if (philos->eating)
// 		printf("is eating\n");
// 	else
// 		printf("is not eating\n");
// 	printf("meals eaten: %d\n", philos->meals_eaten);
// 	printf("last meal: %ld\n", philos->last_meal);
// 	printf("time to die: %ld\n", philos->time_to_die);
// 	printf("time to eat: %ld\n", philos->time_to_eat);
// 	printf("time to sleep: %ld\n", philos->time_to_sleep);
// 	printf("number of philos: %d\n", philos->number_of_philos);
// 	printf("-----------------------------------------\n");
// }

void	set_philos(t_philosoph *philos, t_program *program,
		pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		take_input(philos, av);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].print_lock = &program->print_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].number_of_philos - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		//print_philos_info(philos);
		i++;
	}
}
void	init_program(t_program *program, t_philosoph *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->print_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
