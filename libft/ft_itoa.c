/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:08:11 by cduvivie          #+#    #+#             */
/*   Updated: 2020/01/08 14:28:06 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nbr;

	nbr = (long)n;
	i = 1;
	while ((nbr = nbr / 10))
		i++;
	str = (n == 0) ? (char*)malloc(i + 1) : (char*)malloc(i + 2);
	if (!str)
		return (NULL);
	i = (n < 0) ? i + 1 : i;
	str[i--] = '\0';
	str[0] = n < 0 ? '-' : '\0';
	nbr = (n < 0) ? -(long)n : (long)n;
	str[i] = (n == 0) ? '0' : '\0';
	while (nbr)
	{
		str[i--] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	return (str);
}

/*
**	itoa that gets unsigned integer as input.
*/

char	*ft_uitoa(unsigned int n)
{
	int				i;
	char			*str;
	unsigned long	nbr;

	nbr = (unsigned long)n;
	i = 1;
	while ((nbr = nbr / 10))
		i++;
	str = (n == 0) ? (char*)malloc(i + 1) : (char*)malloc(i + 2);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	str[0] = '\0';
	nbr = (unsigned long)n;
	str[i] = (n == 0) ? '0' : '\0';
	while (nbr)
	{
		str[i--] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	return (str);
}

char	*ft_llitoa(long long int n)
{
	int				i;
	char			*str;
	long long int	nbr;

	nbr = n;
	i = 1;
	while ((nbr = nbr / 10))
		i++;
	str = (n == 0) ? (char*)malloc(i + 1) : (char*)malloc(i + 2);
	if (!str)
		return (NULL);
	i = (n < 0) ? i + 1 : i;
	str[i--] = '\0';
	str[0] = n < 0 ? '-' : '\0';
	nbr = (n < 0) ? -(long long int)n : (long long int)n;
	str[i] = (n == 0) ? '0' : '\0';
	while (nbr)
	{
		str[i--] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	return (str);
}

char	*ft_ullitoa(unsigned long long int n)
{
	int						i;
	char					*str;
	unsigned long long int	nbr;

	nbr = n;
	i = 1;
	while ((nbr = nbr / 10))
		i++;
	str = (n == 0) ? (char*)malloc(i + 1) : (char*)malloc(i + 2);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	str[0] = '\0';
	nbr = n;
	str[i] = (n == 0) ? '0' : '\0';
	while (nbr)
	{
		str[i--] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	return (str);
}
