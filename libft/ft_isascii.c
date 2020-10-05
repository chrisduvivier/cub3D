/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:41:52 by cduvivie          #+#    #+#             */
/*   Updated: 2019/10/17 17:11:27 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	The isascii() function tests for an ASCII character, which is any
**	character between 0 and octal 0177 inclusive.
*/

int		ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
