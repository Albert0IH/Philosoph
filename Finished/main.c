/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:36:49 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/21 10:43:36 by ahamuyel         ###   ########.fr       */
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

int	check_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] < '0' || input[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	valid_input(int ac, char **input)
{
	if (ac != 5 && ac != 6)
	{
		error_msg("ERROR: Check your input");
		error_msg("./philo |philos |time to die |to eat |to think |meals");
		return (1);
	}
	if (ft_atoi(input[1]) > PHILO_MAX || check_input(input[1]))
		return (error_msg("Invalid number of philos\nTry values [0; 200]"),
			1);
	else if (ft_atoi(input[2]) < 60 || check_input(input[2]))
		return (error_msg("Invalid time to die\nTry with values >= 60"),
			1);
	else if (ft_atoi(input[3]) < 60 || check_input(input[3]))
		return (error_msg("Invalid time to eat\nTry with values >= 60"),
			1);
	else if (ft_atoi(input[4]) < 60 || check_input(input[4]))
		return (error_msg("Invalid time to slerep\nTry with values >= 60"),
			1);
	else if (input[5] && (ft_atoi(input[5]) <= 0 || check_input(input[5])))
		return (error_msg("Invalid number of meals for each philo"),
			1);
	return (0);
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philosoph		philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (valid_input(ac, av))
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(av[1]));
	set_philos(philos, &program, forks, av);
	create_thread(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
