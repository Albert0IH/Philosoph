/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 06:51:41 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/06 09:57:46 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophs.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 100);
}
/*------------- Philosofer's actions ---------------*/
void	*philo(void *arg)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = (t_philo *)arg;
	left = philo->id;
	right = (philo->id + 1) % NUM_PHILOS;
	while (*philo->simulation_active)
	{
		// ---- think
		pthread_mutex_lock(philo->print_mutex);
		if (!*philo->simulation_active)
		{
			pthread_mutex_unlock(philo->print_mutex);
			break ;
		}
		printf("Philosopher %d is thinking.\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		sleep(1);
		// ---- take forks
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->forks[left]);
			printf("Philosopher %d took his left's fork.\n", philo->id);
			pthread_mutex_lock(&philo->forks[right]);
			printf("Philosopher %d took his right's fork.\n", philo->id);
		}
		else
		{
			pthread_mutex_lock(&philo->forks[right]);
			printf("Philosopher %d took his right's fork.\n", philo->id);
			pthread_mutex_lock(&philo->forks[left]);
			printf("Philosopher %d took his left's fork.\n", philo->id);
		}
		// ---- eat
		pthread_mutex_lock(philo->print_mutex);
		if (!*philo->simulation_active)
		{
			pthread_mutex_unlock(philo->print_mutex);
			pthread_mutex_unlock(&philo->forks[left]);
			printf("Philosopher %d took his left's fork.\n", philo->id);
			pthread_mutex_unlock(&philo->forks[right]);
			printf("Philosopher %d took his right's fork.\n", philo->id);
			break ;
		}
		printf("Philosopher %d is eating.\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		philo->last_meal_time = get_time_ms();
		sleep(EAT_TIME);
		// ---- leave forks
		pthread_mutex_unlock(&philo->forks[left]);
		printf("Philosopher %d took his left's fork.\n", philo->id);
		pthread_mutex_unlock(&philo->forks[right]);
		printf("Philosopher %d took his right's fork.\n", philo->id);
		// ---- sleep
		pthread_mutex_lock(philo->print_mutex);
		if (!*philo->simulation_active)
		{
			pthread_mutex_unlock(philo->print_mutex);
			break ;
		}
		printf("Philosopher %d is sleeping.\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		sleep(SLEEP_TIME);
		// check if a philos died
		pthread_mutex_lock(philo->print_mutex);
		if (get_time_ms() - philo->last_meal_time > MAX_TIME_WITHOUT_EATING
			&& *philo->simulation_active)
		{
			printf("Philosopher %d has died.\n", philo->id);
			*philo->simulation_active = 0;
		}
		pthread_mutex_unlock(philo->print_mutex);
		if (!*philo->simulation_active)
			break ;
	}
	return (NULL);
}

int	main(void)
{
	pthread_mutex_t	forks[NUM_PHILOS];
	pthread_mutex_t	print_mutex;
	int				simulation_active;
	t_philo			philos[NUM_PHILOS];
	int				i;

	simulation_active = 1;
	i = 0;
	/*-------------INIT MUTEXES-------------*/
	while (i < NUM_PHILOS)
	{
		pthread_mutex_init(&forks[i], NULL);
		philos[i].id = i + 1;
		philos[i].forks = forks;
		philos[i].last_meal_time = get_time_ms();
		philos[i].print_mutex = &print_mutex;
		philos[i].simulation_active = &simulation_active;
		i++;
	}
	pthread_mutex_init(&print_mutex, NULL);
	/*--------------CREATE THREAD'S PHILOS-------------*/
	i = 0;
	while (i < NUM_PHILOS)
	{
		if (pthread_create(&philos[i].thread, NULL, philo, &philos[i]))
		{
			perror("Failed to create philosophos");
			return (1);
		}
		i++;
	}
	/*-----------------WAIT FOR THEADS----------------*/
	i = 0;
	while (i < NUM_PHILOS)
		pthread_join(philos[i++].thread, NULL);
	/*-----------------DESTROY MUTEXES-----------------*/
	i = 0;
	while (i < NUM_PHILOS)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(&print_mutex);
	return (0);
}
