/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:30:26 by cduvivie          #+#    #+#             */
/*   Updated: 2019/10/23 17:15:45 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_words(char const *str, char sep)
{
	int count;

	count = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (*str && *str != sep)
		{
			count++;
			while (*str && *str != sep)
				str++;
		}
	}
	return (count);
}

static char	*malloc_word(char const *str, char sep)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	if (!(word = ft_substr(str, 0, i)))
		return (NULL);
	return (word);
}

static void	free_array(char **array, int i)
{
	if (array)
	{
		while (i >= 0)
		{
			if (array[i])
				free(array[i--]);
		}
		free(array);
	}
}

/*
**	- Description:
**  Allocates (with malloc(3)) and returns an array of strings
**  obtained by splitting `s` using the character `c` as a delimiter.
**  The array must be ended by a NULL pointer.
**	- Return value:
**	The array of new strings result of the split.
**  NULL if the allocation fails.
*/

char		**ft_split(char const *s, char c)
{
	char	**split_tab;
	int		i;

	if (!s)
		return (NULL);
	if (!(split_tab = (char **)malloc(sizeof(char *) * (n_words(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(split_tab[i++] = malloc_word(s, c)))
			{
				free_array(split_tab, i - 1);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
	}
	split_tab[i] = NULL;
	return (split_tab);
}
