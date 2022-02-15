/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing_the_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:22:59 by cmois             #+#    #+#             */
/*   Updated: 2022/02/12 13:53:58 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	put_philo_state(t_philosopher *p, char *state)
{
	printf("%ld\t%d\t%s\n", __gettime(p->pl), p->id, state);
}

void	take_forks(t_philosopher *p)
{
	if (p->id % 2 == 0)
		pthread_mutex_lock(&p->pl->forks[p->lfid]);
	else
		pthread_mutex_lock(&p->pl->forks[p->rfid]);
	pthread_mutex_lock(&p->pl->mutexes[0]);
	if (!p->pl->flag)
		put_philo_state(p, PL_STATE_FORK);
	pthread_mutex_unlock(&p->pl->mutexes[0]);
	if (p->pl->subject[0] == 1)
		return ;
	if (p->id % 2 == 0)
		pthread_mutex_lock(&p->pl->forks[p->rfid]);
	else
		pthread_mutex_lock(&p->pl->forks[p->lfid]);
	pthread_mutex_lock(&p->pl->mutexes[0]);
	if (!p->pl->flag)
		put_philo_state(p, PL_STATE_FORK);
	pthread_mutex_unlock(&p->pl->mutexes[0]);
}

void	eat(t_philosopher *p)
{
	pthread_mutex_lock(&p->pl->mutexes[0]);
	if (!p->pl->flag)
		put_philo_state(p, PL_STATE_EAT);
	++p->ate_food;
	pthread_mutex_unlock(&p->pl->mutexes[0]);
	pthread_mutex_lock(&p->pl->mutexes[1]);
	p->last_ate_time = __gettime(p->pl);
	pthread_mutex_unlock(&p->pl->mutexes[1]);
	__usleep(p->pl->subject[2], p->pl);
	pthread_mutex_unlock(&p->pl->forks[p->rfid]);
	pthread_mutex_unlock(&p->pl->forks[p->lfid]);
}

void	sleep_and_think(t_philosopher *p)
{
	pthread_mutex_lock(&p->pl->mutexes[0]);
	if (!p->pl->flag)
		put_philo_state(p, PL_STATE_SLEEP);
	pthread_mutex_unlock(&p->pl->mutexes[0]);
	__usleep(p->pl->subject[3], p->pl);
	pthread_mutex_lock(&p->pl->mutexes[0]);
	if (!p->pl->flag)
		put_philo_state(p, PL_STATE_THINK);
	pthread_mutex_unlock(&p->pl->mutexes[0]);
}
