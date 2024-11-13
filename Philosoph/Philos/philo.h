/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:47:06 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/13 17:34:49 by ahamuyel         ###   ########.fr       */
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

typedef struct s_philosopher
{
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			start_time;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_philos;
	int				number_time_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_t		thread;
}					t_philosopher;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	t_philosopher	*philos;
}					t_program;

// Utils
int					ft_strlen(char *s);
int					ft_atoi(char *s);
size_t				get_current_time(void);
int					ft_usleep(size_t milissec);
// Checking
int					invalid_arg(char *av);
int					check_inputs(int ac, char **av);
// Initialization
void				take_imput_values(t_philosopher *philos, char **av);
void				set_philos(t_philosopher *philos, t_program *program,
						pthread_mutex_t *forks, char **av);
void				init_forks(pthread_mutex_t *forks, int number_philos);
void				init_program(t_program *program, t_philosopher *philos);
// Threads
void				*routine(void *pointer);
int					create_threads(t_program *program, pthread_mutex_t *fork);
int					philo_dead(t_philosopher *philo);

#endif