/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:47:06 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/20 13:42:07 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philosoph
{
	int				number_of_philos;
	int				number_of_meals;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
}					t_philosoph;

// typedef struct s_program
// {
// 	int				dead_flag;
// 	pthread_mutex_t	dead_lock;
// 	pthread_mutex_t	meal_lock;
// 	pthread_mutex_t	write_lock;
// 	t_philosoph		*philos;
// }					t_program;

// Check
int					check_input(char *input);
int					valid_input(int ac, char **input);
// Initialization
void				take_input(t_philosoph *philo, char **input);
// Threads
// Actions
// Monitor utils
// Utils
int					ft_strlen(char *s);
int					ft_atoi(char *s);
void				print_error_msg(char *msg);

#endif
