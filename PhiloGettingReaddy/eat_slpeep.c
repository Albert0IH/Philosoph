/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_slpeep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:47:02 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/06 03:15:56 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/*------------
--- Mutexes fork_left & fork_right representam 
os os garfos do philo
-----------*/

pthread_mutex_t fork_left;
pthread_mutex_t fork_right;

/*-------------------------
--- Primeiro a thread tenta bloquear os dois garfos, 
ao conseguir, come e em seguida desbloqueia e dorme
------------------------*/

void *philo_cycle(void *arg)
{
    while (1)
    {
        // Eat
        pthread_mutex_lock(&fork_left);
        pthread_mutex_lock(&fork_right);
        printf("Philosoph is eating!\n");
        sleep(2);
        pthread_mutex_unlock(&fork_left);
        pthread_mutex_unlock(&fork_right);
        printf("Philosoph is sleeping!\n");
        sleep(3);
    }
    return (NULL);
}

int main()
{
    pthread_t philo;

    pthread_mutex_init(&fork_left, NULL);
    pthread_mutex_init(&fork_right, NULL);
    if (pthread_create(&philo, NULL, &philo_cycle, NULL))
    {
        perror("Failed to create philo");
        return (1);
    }
    /*-------------
    --- pthread_join para mater o programa em exec
    enquanto a thread do philo realiza seu cíclo
    ------------*/
    pthread_join(philo, NULL);
    pthread_mutex_destroy(&fork_left);
    pthread_mutex_destroy(&fork_right);
    return (0);
}

/*--------------------------------
--- Este exemplo simplifica a lógica de um problema de múltiplos 
filósofos, focando apenas no comportamento cíclico de uma única 
thread, simulando o acesso exclusivo aos garfos.
------------------------------*/
