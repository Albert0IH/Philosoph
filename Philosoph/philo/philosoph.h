/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosoph.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:47:06 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/10 15:59:15 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPH_H
# define PHILOSOPH_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define PHILO_MAX 200
# define EAT_TIME 2
# define SLEEP_TIME 3

typedef struct s_philosoph
{
	int				id;
	int				*simulation;
	long			last_meal;
	int				num_philos;
	int				eat_time;
	int				sleep_time;
	int				time_to_eat;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
}					t_philosoph;

int					check_arg_content(char *av);
int					check_valid_args(char **av);

#endif