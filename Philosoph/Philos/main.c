/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:36:57 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/13 17:06:25 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	invalid_arg(char *av)
{
	while (*av)
	{
		if (*av < '0' || *av > '9')
			return (1);
		av++;
	}
	return (0);
}

int	check_inputs(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (write(2,
				"Usage: ./philo [Num of philos] [time to die] [to eat] [to sleep] [times to eat]\n",
				81), 1);
	if (ft_atoi(av[1]) <= 0 || invalid_arg(av[1]))
		return (write(2, "Invalid number of philos\n", 26), 1);
	if (ft_atoi(av[2]) <= 0 || invalid_arg(av[2]))
		return (write(2, "Invalid time to die\n", 20), 1);
	if (ft_atoi(av[3]) <= 0 || invalid_arg(av[3]))
		return (write(2, "Invalid time to eat\n", 20), 1);
	if (ft_atoi(av[4]) <= 0 || invalid_arg(av[4]))
		return (write(2, "Invalid time to sleep\n", 22), 1);
	if (av[5] && (ft_atoi(av[5]) <= 0 || invalid_arg(av[5])))
		return (write(2, "Invalid times to each philo must eat\n", 38), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_program program;
	t_philosopher philos[PHILO_MAX];
	pthread_mutex_t forks[PHILO_MAX];
	if (check_inputs(ac, av))
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(av[1]));
	set_philos(philos, &program, forks, av);
	create_threads(&program, forks);
	// printf("Aqui!\n");
	// 	// destory all
	return (0);
}