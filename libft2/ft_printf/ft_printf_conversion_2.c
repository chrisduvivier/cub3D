/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:37:40 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/25 14:29:21 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf_lst	*ft_pf_convert_d(t_printf_lst *node, long long int i)
{
	if (i == 0)
		node->zero = 1;
	if (!(node->str = ft_llitoa(i)))
	{
		node->error = 1;
		return (node);
	}
	node->num_conv = 1;
	node->str_len = ft_strlen(node->str);
	return (node);
}

/*
**	NOTES:
**	flag ' ' and flag '+' results in undefined behavior
**	with 'u' conversion specifier.
*/

t_printf_lst	*ft_pf_convert_u(t_printf_lst *node,
								unsigned long long int u)
{
	if (u == 0)
		node->zero = 1;
	if (!(node->str = ft_ullitoa(u)))
	{
		node->error = 1;
		return (node);
	}
	node->num_conv = 1;
	node->str_len = ft_strlen(node->str);
	return (node);
}

/*
**	handling of `%p` format.
*/

t_printf_lst	*ft_pf_convert_p(t_printf_lst *node, uintmax_t num)
{
	if (num == 0)
		node->zero = 1;
	if (!(node->str = ft_pf_append_hex_format(ft_itohex(num, 0), 'x')))
	{
		node->error = 1;
		return (node);
	}
	node->str_len = ft_strlen(node->str);
	return (node);
}

/*
**	handling of `%x and %X` format.
*/

t_printf_lst	*ft_pf_convert_x(t_printf_lst *node,
								unsigned long long u, char form)
{
	if (u == 0)
		node->zero = 1;
	node->str = (form && form == 'X') ? ft_itohex(u, 'X') : ft_itohex(u, 'x');
	if (!node->str)
	{
		node->error = 1;
		return (node);
	}
	node->str_len = ft_strlen(node->str);
	return (node);
}
