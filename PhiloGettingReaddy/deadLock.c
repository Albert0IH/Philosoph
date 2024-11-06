/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadLock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:22:34 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/06 02:53:14 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*-----------
--- As mutexes são declaradas de forma global 
para serem usadas pelas duas threads
-----------*/

pthread_mutex_t	mutex_1;
pthread_mutex_t	mutex_2;

void	*thread_func1(void *arg)
{
	pthread_mutex_lock(&mutex_1);
	printf("Thread 1 locked mutex 1\n");
	sleep(1);
	pthread_mutex_lock(&mutex_2);
	printf("Thread 1 locked mutex 2\n");
	pthread_mutex_unlock(&mutex_1);
	pthread_mutex_unlock(&mutex_2);
	return (NULL);
}

void	*thread_func2(void *arg)
{
	pthread_mutex_lock(&mutex_1);
	printf("Thread 2 locked mutex 2\n");
	sleep(1);
	pthread_mutex_lock(&mutex_2);
	printf("Thread 2 locked mutex 1\n");
	pthread_mutex_unlock(&mutex_1);
	pthread_mutex_unlock(&mutex_2);
	return (NULL);
}

/*-------------------
--- Se thread_func1 pegar mutex_1 e thread_func2 pegar
mutex_2, ambas ficarão a espera da liberacao da segunda
mutex para continuar, e isso provoca deadlock!

--- Para evitar isso, é sempre bom bloquear as mutexes na
mesma ordem, ou usar uma única mutex que controle a section 
crítica inteira, se possível!
------------------*/

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_mutex_init(&mutex_1, NULL);
	pthread_mutex_init(&mutex_2, NULL);
	if (pthread_create(&thread1, NULL, &thread_func1, NULL))
	{
		perror("Failed to create thread 1");
		return (1);
	}
	if (pthread_create(&thread2, NULL, &thread_func2, NULL))
	{
		perror("Failed to create thread 2");
		return (1);
	}
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex_1);
    pthread_mutex_destroy(&mutex_2);
    return (0);
}
