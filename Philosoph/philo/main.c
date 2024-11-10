/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:36:49 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 19:00:44 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_content(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **av)
{
	if (atoi(av[1]) > PHILO_MAX || atoi(av[1]) <= 0 || check_arg_content(av[1]))
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (atoi(av[2]) <= 0 || check_arg_content(av[2]))
		return (write(2, "Invalid time to die\n", 21), 1);
	if (atoi(av[3]) <= 0 || check_arg_content(av[3]))
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (atoi(av[4]) <= 0 || check_arg_content(av[4]))
		return (write(2, "Invalid time to sleap\n", 23), 1);
	if (atoi(av[5]) <= 0 || check_arg_content(av[5]))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}
int	main(int argc, char **argv)
{
	t_simulation		program;
	t_philosoph			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_valid_args(argv) == 1)
		return (1);
	init_simulation(&program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	create_thread(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
