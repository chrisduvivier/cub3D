/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_apply_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 08:50:04 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/25 14:31:59 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	`#` format adds hexadecimal format to the begining of string (xX format).
*/

static t_printf_lst	*apply_sharp(t_printf_lst *node)
{
	if (!(ft_pf_is_zero(node->str)))
	{
		node->str = ft_pf_append_hex_format(node->str, node->percent);
		if (!node->str)
		{
			node->error = 1;
			return (node);
		}
		node->str_len = ft_strlen(node->str);
	}
	return (node);
}

/*
**	`'` flag adds `.` seperator to decimal number.
*/

static char			*ft_thousand_sep(char *str, size_t len, size_t i, size_t j)
{
	size_t	num_sep;
	char	*res;

	num_sep = (str[0] == '+' || str[0] == '-') ? (len - 1) / 3 : len / 3;
	if (!(res = ft_calloc(len + num_sep + 1, sizeof(char))))
		return (NULL);
	if (str[0] == '+' || str[0] == '-')
	{
		res[i++] = str[j++];
		while (i - 1 < (len - 1) % 3)
			res[i++] = str[j++];
	}
	else
		while (i < len % 3)
			res[i++] = str[j++];
	while (j < len && num_sep--)
	{
		if (i != 0 && !(i == 1 && (str[0] == '+' || str[0] == '-')))
			res[i++] = ',';
		res[i++] = str[j++];
		res[i++] = str[j++];
		res[i++] = str[j++];
	}
	return (res);
}

/*
**	Apply `'` flag to string.
*/

t_printf_lst		*ft_pf_apply_thousand_sep(t_printf_lst *node)
{
	char *tmp;

	if (!(tmp = ft_thousand_sep(node->str, node->str_len, 0, 0)))
	{
		node->error = 1;
		return (node);
	}
	free(node->str);
	node->str = tmp;
	node->str_len = ft_strlen(node->str);
	return (node);
}

/*
**	- Description
**	 Apply flags to the formated string.
**	- Notes
**	flag '0' is ignored when flag '-' is present
**	flag '0' results in undefined behavior with 's' conversion specifier.
**	flag '0' results in undefined behavior with 'p'
*/

t_printf_lst		*ft_pf_apply_flags(va_list *valist, t_printf_lst *node)
{
	if ((node->flags.space || node->flags.plus) && node->num_conv)
		node = ft_pf_append_sign(node);
	if (!node->error && node->flags.apostrophe
		&& ft_strchr("diu", node->percent))
		node = ft_pf_apply_thousand_sep(node);
	if (!node->error && node->flags.precision && node->percent != '%')
		node = ft_pf_apply_precision(node);
	if (!node->error && node->flags.sharp && ft_strchr("xX", node->percent))
		node = apply_sharp(node);
	if (!node->error && node->flags.min_w && node->flags.min_w > node->str_len)
		node = ft_pf_apply_min_w(node);
	return (node);
}
