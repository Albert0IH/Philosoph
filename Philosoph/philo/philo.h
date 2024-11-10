/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:47:06 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 23:45:35 by ahamuyel         ###   ########.fr       */
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
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				number_of_philos;
	int				number_times_to_eat;
	int				*dead;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philosoph;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	t_philosoph		*philos;
}					t_program;

// Check
int					check_content_arg(char *av);
int					check_valid_args(char **av);

// Initialization
void				take_input(t_philosoph *philos, char **av);
void				print_philos_info(t_philosoph *philos);
void				set_philos(t_philosoph *philos, t_program *program,
						pthread_mutex_t *forks, char **av);
						void init_program(t_program *program, t_philosoph *philos);
// Threads

// Actions

// Monitor utils

// Utils
int					ft_strlen(char *s);
int					ft_atoi(char *s);
int					ft_usleep(size_t milissec);
size_t				get_current_time(void);

#endif