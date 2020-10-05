/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:49:41 by chrisduvivi       #+#    #+#             */
/*   Updated: 2019/10/30 16:44:02 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Adds the element new at the end of the list.
*/

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	if (alst && new)
	{
		if (!(*alst))
			*alst = new;
		else
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
	}
}
