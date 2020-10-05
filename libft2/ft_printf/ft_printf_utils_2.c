/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:04:46 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/25 14:27:18 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	The atoi() function converts the initial portion of the string pointed
**	to by str to int representation.
**	Return 0 by default
*/

int		ft_pf_atoi(const char **format)
{
	unsigned long long	result;

	result = 0;
	while (**format >= '0' && **format <= '9')
	{
		result = result * 10 + (**format - '0');
		(*format)++;
	}
	return (int)(result);
}
