/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:13:22 by cmois             #+#    #+#             */
/*   Updated: 2022/02/13 14:37:46 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_mutexes(t_pl *pl)
{
	int	i;
	int	n;

	i = 0;
	n = sizeof(pl->mutexes) / sizeof(pthread_mutex_t);
	while (i < n)
	{
		pthread_mutex_init(&pl->mutexes[i], NULL);
		++i;
	}
	pl->forks = malloc_and_memset(pl->subject[0] * sizeof(pthread_mutex_t));
	if (!pl->forks)
		return (false);
	i = 0;
	while (i < pl->subject[0])
	{
		pthread_mutex_init(&pl->forks[i], NULL);
		++i;
	}
	return (true);
}

bool	init_philos(t_pl *pl)
{
	long	i;

	pl->philosophers = malloc_and_memset(pl->subject[0]
			* sizeof(t_philosopher));
	if (!pl->philosophers)
		return (false);
	i = -1;
	while (++i < pl->subject[0])
	{
		pl->philosophers[i].pl = pl;
		pl->philosophers[i].id = i + 1;
		pl->philosophers[i].lfid = i;
		pl->philosophers[i].rfid = (i + 1) % pl->subject[0];
		pl->philosophers[i].ate_food = 0;
		pl->philosophers[i].last_ate_time = 0;
		pl->philosophers[i].had_enough_food = false;
	}
	return (true);
}

bool	init(t_pl *pl)
{
	pl->i = 0;
	pl->flag = 0;
	return (init_mutexes(pl) && init_philos(pl));
}

int	__getflag(t_pl *pl)
{
	int	flag;

	pthread_mutex_lock(&pl->mutexes[0]);
	flag = pl->flag;
	pthread_mutex_unlock(&pl->mutexes[0]);
	return (flag);
}

int	__setflag(t_philosopher *p, int new_val)
{	
	int	flag;

	pthread_mutex_lock(&p->pl->mutexes[0]);
	if (new_val)
		p->pl->flag = new_val;
	flag = p->pl->flag;
	pthread_mutex_unlock(&p->pl->mutexes[0]);
	return (flag);
}
