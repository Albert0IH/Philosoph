/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 06:40:20 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/08 12:30:11 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NUM_PHILOS 6
# define EAT_TIME 1
# define SLEEP_TIME 3
# define MAX_TIME_WITHOUT_EATING 4

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	int				*simulation_active;
}					t_philo;

long				get_time_ms(void);

// Routine

void				take_forks(t_philo *philo, int left, int right,
						long start_time);

void				philo_eat_sleep_think(t_philo *philo, int left, int right,
						long start_time);
// Iniit philos
void				*philo_routine(void *arg);
void				initialize_mutexes(pthread_mutex_t *forks,
						pthread_mutex_t *print_mutex);
void				initialize_philos(t_philo *philo, pthread_mutex_t *forks,
						pthread_mutex_t *print_mutex, int *simulation_active);
void				create_philos_threads(t_philo *philo);
void				destroy_mutexes(pthread_mutex_t *forks,
						pthread_mutex_t *print_mutex);

#endif
