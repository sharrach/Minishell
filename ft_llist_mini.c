/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:02:41 by sharrach          #+#    #+#             */
/*   Updated: 2022/10/26 13:54:23 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*ft_mini_lstlast(t_mini *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_mini_lstadd_back(t_mini **lst, t_mini *new)
{
	if (*lst)
		ft_mini_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_mini	*ft_mini_lstnew(char **cmd, t_lst *redir)
{
	t_mini	*new;

	new = malloc(sizeof(t_mini) * 1);
	if (new == 0)
		return (NULL);
	new->cmd = cmd;
    new->pipe[STDIN_FILENO] = STDIN_FILENO;
    new->pipe[STDOUT_FILENO] = STDOUT_FILENO;
	new->redir = redir;
	new->next = NULL;
	return (new);
}

void	ft_mini_lstclear(t_mini **lst)
{
	t_mini	*holder;

	if (!lst)
		return;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
        free_2d(holder->cmd);
		ft_lst_lstclear(&holder->redir);
        free(holder);
	}
	*lst = NULL;
}
