/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:36:49 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/11 06:14:40 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_content_arg(char *av)
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
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| check_content_arg(av[1]))
		return (write(2, "Invalid philosopher's number\n", 30), 1);
	if (ft_atoi(av[2]) <= 0 || check_content_arg(av[2]))
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(av[3]) <= 0 || check_content_arg(av[3]))
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(av[4]) <= 0 || check_content_arg(av[4]))
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (av[5] && (ft_atoi(av[5]) <= 0 || check_content_arg(av[5])))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}
int	main(int ac, char **av)
{
	t_program		program;
	t_philosoph		philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (write(2,
				"Wrong argument count\nTry ./philo [time to die] [time to eat] [time to sleep] [times to each must eat]\n",
				103), 1);
	if (check_valid_args(av))
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(av[1]));
	set_philos(philos, &program, forks, av);
	create_thread(&program, forks);
	destory_all(NULL, &program, forks);
	// printf("Number of Philosophers: %d\n", program.philos[0].number_of_philos);
	// printf("Philos array address: %p\n", (void *)program.philos);
	// free(philos);
	// free(forks);
	return (0);
}
