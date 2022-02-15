/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:19:50 by cmois             #+#    #+#             */
/*   Updated: 2022/02/13 13:14:31 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*malloc_and_memset(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	memset(ret, 0x00, size);
	return (ret);
}

bool	is_char_digit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	is_str_numeric(char *str)
{
	while (*str)
	{
		if (!is_char_digit(*str))
			return (false);
		++str;
	}
	return (true);
}

long	str_to_long(char *str)
{
	long	ret;

	ret = 0;
	while (*str && is_char_digit(*str))
	{
		ret = ret * 10 + *str - 48;
		++str;
	}
	return (ret);
}
