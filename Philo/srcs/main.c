/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:31:23 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/08 13:05:00 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(void)
{
	pthread_mutex_t forks[NUM_PHILOS];
	pthread_mutex_t print_mutex;
	t_philo philos[NUM_PHILOS];
	int simulation;
	int i;

    simulation = 1;
	initialize_mutexes(forks, &print_mutex);
	initialize_philos(philos, forks, &print_mutex, &simulation);
	create_philos_threads(philos);
	i = 0;
	while (i < NUM_PHILOS)
		pthread_join(philos[i++].thread, NULL);
	destroy_mutexes(forks, &print_mutex);
	return (0);
}