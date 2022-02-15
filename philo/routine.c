/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:27:11 by cmois             #+#    #+#             */
/*   Updated: 2022/02/12 13:54:47 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thread_creation(t_pl *pl)
{
	long	i;

	i = -1;
	while (++i < pl->subject[0])
	{
		if (pthread_create(&pl->philosophers[i].t1id, NULL,
				&routine1, &pl->philosophers[i]))
			destroy_all(pl);
	}
}

void	*routine1(void *arg)
{
	t_philosopher	*p;
	void			*b;

	b = NULL;
	p = (t_philosopher *)arg;
	if (!(p->id % 2))
		__usleep(50, p->pl);
	while (!__setflag(p, 0) && !p->had_enough_food)
	{
		take_forks(p);
		if (p->pl->subject[0] == 1)
		{
			pthread_mutex_unlock(&p->pl->forks[p->rfid]);
			return (NULL);
		}
		eat(p);
		if (is_philo_bigboi(p))
			return (NULL);
		sleep_and_think(p);
		__usleep(1, p->pl);
	}
	return (b);
}

void	*routine2(void *arg)
{
	t_philosopher	*p;

	p = (t_philosopher *)arg;
	while (1)
	{
		if (is_philo_deadboi(p))
		{
			return (NULL);
		}
		__usleep(1, p->pl);
	}
}
