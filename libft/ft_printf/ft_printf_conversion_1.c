/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:04:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/01/09 11:00:12 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_chartostr(int i)
{
	char *str;

	if (!(str = ft_calloc(2, sizeof(char))))
		return (NULL);
	str[0] = (char)i;
	str[1] = '\0';
	return (str);
}

/*
**	handling of `%c` format.
*/

t_printf_lst	*ft_pf_convert_c(t_printf_lst *node, uintmax_t c)
{
	if (!(node->str = ft_chartostr(c)))
	{
		node->error = 1;
		return (node);
	}
	node->str_len = 1;
	return (node);
}

/*
**	Print "%". Does not get affected by any flags.
*/

t_printf_lst	*ft_pf_convert_pc(t_printf_lst *node, int c)
{
	if (!(node->str = ft_chartostr('%')))
	{
		node->error = 1;
		return (node);
	}
	node->str_len = 1;
	return (node);
}

/*
**	handling of `%s` format. returns `(null)` when the given
**	string src is NULL. strdup otherwise.
*/

t_printf_lst	*ft_pf_convert_s(t_printf_lst *node, const char *src)
{
	node->str = (!src) ? ft_strdup("(null)") : ft_strdup(src);
	if (!node->str)
	{
		node->error = 1;
		return (node);
	}
	node->str_len = ft_strlen(node->str);
	return (node);
}
