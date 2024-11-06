/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 06:40:20 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/06 08:34:26 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHS_H
# define PHILOSOPH_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NUM_PHILOS 6
# define EAT_TIME 2
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

#endif
