/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:39:01 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/09 18:24:07 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i ++;
		lst = lst->next;
	}
	return (i);
}

t_env	*ft_env_lstlast(t_env *env)
{
	while (env)
	{
		if (!env->next)
			break ;
		env = env->next;
	}
	return (env);
}

void	ft_env_lstadd_back(t_env **env, t_env *new)
{
	if (*env)
	{
		new->prev = ft_env_lstlast(*env);
		ft_env_lstlast(*env)->next = new;
	}
	else
		*env = new;
}

t_env	*ft_env_lstnew(char *var, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env) * 1);
	if (new == 0)
		return (NULL);
    new->var = var;
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_env_lstclear(t_env **env)
{
	t_env	*holder;

	if (!env)
		return;
	while (*env)
	{
		holder = *env;
		*env = (*env)->next;
        free(holder->var);
        free(holder->content);
        free(holder);
	}
	*env = NULL;
}
