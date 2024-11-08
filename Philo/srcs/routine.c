/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:41:17 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/08 13:10:34 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 100 + tv.tv_sec / 1000);
}

void	take_forks(t_philo *philo, int left, int right, long start_time)
{
	long	time;

	time = get_time_ms() - start_time;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[left]);
		printf("%ld %d took his left's fork.\n", time, philo->id);
		pthread_mutex_lock(&philo->forks[right]);
		printf("%ld %d took his right's fork.\n", time, philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[right]);
		printf("%ld %d took his right's fork.\n", time, philo->id);
		pthread_mutex_lock(&philo->forks[left]);
		printf("%ld %d took his left's fork.\n", time, philo->id);
	}
}

void	philo_eat_sleep_think(t_philo *philo, int left, int right,
		long start_time)
{
	long	time;

	time = get_time_ms() - start_time;
	pthread_mutex_lock(philo->print_mutex);
	if (*philo->simulation_active)
		;
	printf("%ld %d is eating.\n", time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	philo->last_meal_time = get_time_ms();
	sleep(EAT_TIME);
	pthread_mutex_unlock(&philo->forks[left]);
	pthread_mutex_unlock(&philo->forks[right]);
	pthread_mutex_lock(philo->print_mutex);
	if (*philo->simulation_active)
		printf("%ld %d is sleeping.\n", get_time_ms() - start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	sleep(SLEEP_TIME);
	pthread_mutex_lock(philo->print_mutex);
	if (*philo->simulation_active)
		printf("%ld %d is thinking.\n", get_time_ms() - start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	sleep(1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		left;
	int		right;
	long	start_time;

	philo = (t_philo *)arg;
	left = philo->id;
	right = (philo->id + 1) % NUM_PHILOS;
	start_time = get_time_ms();
	while (*philo->simulation_active)
	{
		take_forks(philo, left, right, start_time);
		philo_eat_sleep_think(philo, left, right, start_time);
		if (get_time_ms() - philo->last_meal_time > MAX_TIME_WITHOUT_EATING)
		{
			pthread_mutex_lock(philo->print_mutex);
			if (*philo->simulation_active)
			{
				printf("%ld %d has died.\n", get_time_ms() - start_time,
					philo->id);
				*philo->simulation_active = 0;
			}
			pthread_mutex_unlock(philo->print_mutex);
			break ;
		}
	}
	return (NULL);
}
