/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsMutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 01:42:02 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/06 02:18:36 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_TH 10
#define INCREMNT 100

int				counter;
pthread_mutex_t	mutex;

void	*increment(void *arg)
{
	int	i;

	i = 0;
	/*-----------------
	--- Iniciar o incremento de counter
	depois do lock e antes de unlock, para
	evitar race conditions e possiveis
	valores inconsistentes
	-----------------*/
	while (i < INCREMNT)
	{
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

/*---------------------------
// Se não bloquear o acesso a func increment, todas
as threads vão tentar acessá-la incrementado "counter"
ao mesmo tempo, e isso pode resultar em resultado
inesperado!
-----------------------------*/

int	main(void)
{
	int			i;
	pthread_t	threads[NUM_TH];

	//*****************INICIALIZANDO A MUTEX*****************//
	if (pthread_mutex_init(&mutex, NULL))
	{
		perror("Failed to init mutex");
		return (1);
	}
	/*----------------------
	--- Criar todas as threads primeiro e, em seguida esperar 
	por elas com pthread_join, para garantir que todas as threads
	completem sua tarefa antes que o programa principal continue ou
	finalize!
	-----------------------*/
	i = 0;
	while (i < NUM_TH)
	{
		if (pthread_create(&threads[i++], NULL, &increment, NULL))
		{
			perror("Failed to create thread");
			return (1);
		}
	}
	i = 0;
	while (i < NUM_TH)
	{
		if (pthread_join(threads[i++], NULL))
		{
			perror("Failed to join thread");
			return (1);
		}
	}
	//*****************FECHANDO A MUTEX*****************//
	pthread_mutex_destroy(&mutex);
	printf("Final counter value: %d\n", counter);
	return (0);
}
