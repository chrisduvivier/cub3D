/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:37:05 by cduvivie          #+#    #+#             */
/*   Updated: 2020/03/02 16:38:10 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  returns 1 (true) if the char is a space char.
**  retunrs 0 (false) otherwise.
*/

int			ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}

void		ft_skip_space(char **str)
{
	while (*str && ft_isspace(**str))
		(*str)++;
}
