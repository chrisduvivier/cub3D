/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:53:01 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/05 13:31:49 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The atoi() function converts the initial portion of the string pointed
**	to by str to int representation.
*/

int			ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > LONG_MAX)
			return (sign == -1) ? (0) : (-1);
		str++;
	}
	return (int)(sign * result);
}

/*
**	The atoi() function converts the initial portion of the string pointed
**	to by str to int representation. pointer to str moves as the atoi reads.
**	It therefore finishes where the string of number finishes
*/

int			ft_atoi_w_p(const char **str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		sign = (**str == '-') ? -1 : 1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		if (result > LONG_MAX)
			return (sign == -1) ? (0) : (-1);
		(*str)++;
	}
	return (int)(sign * result);
}
