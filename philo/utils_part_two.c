/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_part_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:20:48 by cmois             #+#    #+#             */
/*   Updated: 2022/02/12 14:00:38 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	__gettime(t_pl *pl)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - pl->start_time.tv_sec) * 1000
		+ (now.tv_usec - pl->start_time.tv_usec) / 1000);
}

void	__usleep(long int time, t_pl *pl)
{
	long int	start;

	start = 0;
	start = __gettime(pl);
	while (1)
	{
		if (__gettime(pl) - start >= time)
			return ;
		usleep(50);
	}
}
