/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:36:49 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/20 13:56:07 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(char *s)
{
	int				i;
	int				sig;
	unsigned long	n;

	i = 0;
	sig = 1;
	n = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\f'
		|| s[i] == '\r' || s[i] == '\v')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			n *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return (n * sig);
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

void	print_error_msg(char *msg)
{
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}

int	valid_input(int ac, char **input)
{
	if (ac != 5 && ac != 6)
	{
		print_error_msg("ERROR\nCheck your input\nTry: ./philo [n philos] [time to die] [to eat] [to think] ([times to eat] optional)");
		return (1);
	}
	if (ft_atoi(input[1]) > PHILO_MAX || check_input(input[1]))
		return (print_error_msg("Invalid time number of philos\nTry with values > 0 && <= 200"), 1);
	else if (ft_atoi(input[2]) < 60 || check_input(input[2]))
		return (print_error_msg("Invalid time to die\nTry with values >= 60"), 1);
	else if (ft_atoi(input[3]) < 60 || check_input(input[3]))
		return (print_error_msg("Invalid time to eat\nTry with values >= 60"), 1);
	else if (ft_atoi(input[4]) < 60 || check_input(input[4]))
		return (print_error_msg("Invalid time to slerep\nTry with values >= 60"), 1);
	else if (input[5] && (ft_atoi(input[5]) <= 0 || check_input(input[5])))
		return (print_error_msg("Invalid number of meals for each philo\nTry with values > 0"), 1);
	return (0);
}

void print_philo_info(t_philosoph *philos, char **av)
{
	printf("Number of philo [%d] \n", philos->number_of_philos);
	printf("Time to die [%ld] \n", philos->time_to_die);
	printf("Time to eat [%ld] \n", philos->time_to_eat);
	printf("Time to sleep [%ld] \n", philos->time_to_sleep);
	if (av[5])
		printf("NUmber of meals [%d] \n", philos->number_of_meals);
	else
	{
		free(philos);
		return ;
	}
	free(philos);
}

int	main(int ac, char **av)
{
	t_philosoph *philos;
	if (valid_input(ac, av))
		return (1);
	philos = malloc(sizeof(t_philosoph));
	take_input(philos, av);
	print_philo_info(philos, av);
	return (0);
}
