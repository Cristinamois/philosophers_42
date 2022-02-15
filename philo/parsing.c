/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:18:27 by cmois             #+#    #+#             */
/*   Updated: 2022/02/12 13:54:02 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	parser(t_pl *pl, int ac, char *av[])
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		if (!is_str_numeric(av[i]))
			return (false);
		pl->subject[i] = str_to_long(av[i]);
		if (!pl->subject[i] || pl->subject[i] > INT_MAX)
			return (false);
	}
	if (ac == 4)
		pl->subject[4] = -1;
	return (true);
}
