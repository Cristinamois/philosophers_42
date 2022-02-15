/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:11:50 by cmois             #+#    #+#             */
/*   Updated: 2022/02/11 16:11:50 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_all(t_pl *pl)
{
	int	i;
	int	n;

	i = 0;
	n = sizeof(pl->mutexes) / sizeof(pthread_mutex_t);
	while (i < n)
	{
		pthread_mutex_destroy(&pl->mutexes[i]);
		++i;
	}
	if (pl->philosophers)
		free(pl->philosophers);
	i = 0;
	while (i < pl->subject[0])
	{
		pthread_mutex_destroy(&pl->forks[i]);
		++i;
	}
	if (pl->forks)
		free(pl->forks);
}

int	main(int ac, char *av[])
{
	t_pl	pl;
	long	i;

	--ac;
	++av;
	if (ac != 4 && ac != 5)
	{
		printf("Args not good\n");
		return (1);
	}
	if (!parser(&pl, ac, av) || !init(&pl))
	{
		printf("parser failed || init_failed\n");
		return (2);
	}
	gettimeofday(&pl.start_time, NULL);
	thread_creation(&pl);
	single_monitor(&pl);
	i = -1;
	while (++i < pl.subject[0])
		pthread_join(pl.philosophers[i].t1id, NULL);
	destroy_all(&pl);
	return (0);
}
