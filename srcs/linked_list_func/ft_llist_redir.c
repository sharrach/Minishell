/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:02:41 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/16 12:57:26 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lst	*ft_lst_lstlast(t_lst *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_lst_lstadd_back(t_lst **lst, t_lst *new)
{
	if (*lst)
	{
		new->prev = ft_lst_lstlast(*lst);
		ft_lst_lstlast(*lst)->next = new;

	}
	else
		*lst = new;
}

t_lst	*ft_lst_lstnew(char *content, int type)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst) * 1);
	if (new == 0)
		return (NULL);
	new->content = content;
    new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lst_lstclear(t_lst **lst)
{
	t_lst	*holder;

	if (!lst)
		return;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
        free(holder->content);
        free(holder);
	}
	*lst = NULL;
}
