/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:49:23 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/06 01:39:43 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*---------------------------Create Semple thread---------------------------*/

void *compute_tasks(void *arg)
{
	int *num;

	num = (int *)arg;
	*num *= 2;
	return (NULL);
}

int main()
{
	pthread_t thread;
	int num;

	num = 2;
	if (pthread_create(&thread, NULL, &compute_tasks, &num))
	{
		perror("Failed to create thread");
		return (1);
	}
	if (pthread_join(thread, NULL))
	{
		perror("Failed to create thread");
		return (1);
	}
	printf("Result: %d\n", num);
	return (0);
}


/*---------------------------------Create Multiple threads--------------------------------*/
/*#define NUM_TH 5

pthread_t	th[NUM_TH];

void	*routine(void *arg)
{
	int	th_id;

	th_id = *(int *)arg;
	printf("Hi, from thread ID: %d\n", th_id);
	return (NULL);
}

int	main(void)
{
	int	i;
	int	th_ids[NUM_TH];

	i = 0;
	while (i < NUM_TH)
	{
		th_ids[i] = i + 1;
		if (pthread_create(&th[i], NULL, &routine, &th_ids[i]))
		{
			perror("Failed to create thread\n");
			exit(EXIT_FAILURE);
		}
		//sleep(1);
		i++;
	}
	i = 0;
	while (i < NUM_TH)
	{
		if (pthread_join(th[i++], NULL))
		{
			perror("Failed to join thread\n");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
*/
