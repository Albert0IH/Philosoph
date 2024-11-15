/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:36:49 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/15 14:55:36 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(char *s)
{
	unsigned long	n;
	int				sig;
	int				i;

	n = 0;
	sig = 1;
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == '\r')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sig = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return (sig * n);
}

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
		return (write(2, "Invalid number of philosophers\n", 32), 1);
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
		return (write(2, "./philo [death] [meal] [spleep] [number of meals]\n",
				51), 1);
	if (check_valid_args(av))
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(av[1]));
	set_philos(philos, &program, forks, av);
	create_thread(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
