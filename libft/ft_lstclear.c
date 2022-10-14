/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 21:04:14 by sharrach          #+#    #+#             */
/*   Updated: 2021/11/23 00:14:11 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*holder;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(holder, del);
	}
	*lst = NULL;
}
