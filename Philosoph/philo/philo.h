/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:47:06 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 18:54:02 by ahamuyel         ###   ########.fr       */
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
	pthread_mutex_t	*r_forks;
	pthread_mutex_t	*l_forks;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philosoph;

typedef struct s_simulation
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	t_philosoph		*philos;
}					t_simulation;

// Check
int					check_arg_content(char *av);
int					check_valid_args(char **av);
int					check_dead(t_philosoph *philo);
int					philos_dead(t_philosoph *philo, size_t time_to_die);
// Initialization
void				init_inputs(t_philosoph *philos, char **av);
void				init_philos(t_philosoph *philos, t_simulation *simulation,
						pthread_mutex_t *forks, char **av);
void				init_forks(pthread_mutex_t *forks, int philo_number);
void				init_simulation(t_simulation *simulation,
						t_philosoph *philo);
void				destroy_all(char *s, t_simulation *simulation,
						pthread_mutex_t *forks);

// Threads
int					create_thread(t_simulation *simulation,
						pthread_mutex_t *forks);

// Actions
void				*philo_routine(void *arg);
void				thinking(t_philosoph *philo);
void				sleeping(t_philosoph *philo);
void				eating(t_philosoph *philo);

// Monitor utils
void				print_msg(char *s, t_philosoph *philo, int id);
int					search_death(t_philosoph *philos);
int					check_if_all_ate(t_philosoph *philos);
void				*monitor(void *arg);
// Utils
int					ft_strlen(char *s);
int					ft_atoi(char *s);
int					ft_usleep(size_t milissec);
size_t				get_current_time(void);

#endif