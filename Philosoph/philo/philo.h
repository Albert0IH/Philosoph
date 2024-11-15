/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:47:06 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/15 13:49:58 by ahamuyel         ###   ########.fr       */
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
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philosoph;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philosoph		*philos;
}					t_program;

// Check
int					check_content_arg(char *av);
int					check_valid_args(char **av);

// Initialization
void				take_input(t_philosoph *philos, char **av);
void				set_philos(t_philosoph *philos, t_program *program,
						pthread_mutex_t *forks, char **av);
void				init_program(t_program *program, t_philosoph *philos);
void				init_forks(pthread_mutex_t *forks, int philos_number);
// Threads
int					philo_dead(t_philosoph *philo);
void				*philos_rotine(void *arg);
int					create_thread(t_program *program, pthread_mutex_t *forks);
// Actions
void				thinking(t_philosoph *philo);
void				sleeping(t_philosoph *philo);
void				eating(t_philosoph *philo);
void				print_msg(char *s, t_philosoph *philo, int id);
// Monitor utils
void				print_msg(char *s, t_philosoph *philo, int id);
int					kill_philo(t_philosoph *philo, size_t time_to_die);
int					check_death(t_philosoph *philos);
int					check_if_all_ate(t_philosoph *philos);
void				*monitor(void *arg);
// Utils
int					ft_strlen(char *s);
int					ft_atoi(char *s);
int					ft_usleep(size_t milissec);
size_t				get_current_time(void);

void				destroy_all(char *s, t_program *program,
						pthread_mutex_t *forks);
void				take_forks(t_philosoph *philo);

#endif
