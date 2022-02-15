/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_on_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:26:09 by cmois             #+#    #+#             */
/*   Updated: 2022/02/11 20:47:55 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_philo_bigboi(t_philosopher *p)
{
	long	i;

	if (p->pl->subject[4] != -1 && p->ate_food >= p->pl->subject[4])
	{
		p->had_enough_food = true;
		pthread_mutex_lock(&p->pl->mutexes[2]);
		i = ++p->pl->i;
		pthread_mutex_unlock(&p->pl->mutexes[2]);
		if (i == p->pl->subject[0])
		{
			__setflag(p, 2);
			return (true);
		}
	}
	return (false);
}

bool	is_philo_deadboi(t_philosopher *p)
{
	long	last_ate_time;

	pthread_mutex_lock(&p->pl->mutexes[1]);
	last_ate_time = p->last_ate_time;
	pthread_mutex_unlock(&p->pl->mutexes[1]);
	if (__gettime(p->pl) - last_ate_time >= p->pl->subject[1])
	{
		pthread_mutex_lock(&p->pl->mutexes[0]);
		if (!p->pl->flag)
			put_philo_state(p, PL_STATE_DIE);
		pthread_mutex_unlock(&p->pl->mutexes[0]);
		__setflag(p, 1);
		return (true);
	}
	return (false);
}

void	single_monitor(t_pl *pl)
{
	long	i;

	while (1)
	{
		i = -1;
		while (++i < pl->subject[0])
		{
			if (is_philo_deadboi(&pl->philosophers[i]))
			{
				return ;
			}
		}
		__usleep(1, pl);
	}
}
