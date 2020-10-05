/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:39:07 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/26 14:04:56 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The strdup() function allocates sufficient memory for a copy of the
**	string s1, does the copy, and returns a pointer to it.
*/

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*p;

	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	p = str;
	while (*s1)
		*p++ = *s1++;
	*p = '\0';
	return (str);
}
