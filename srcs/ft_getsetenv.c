/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:26:21 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/23 12:32:51 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_setenv(t_env **env, char *var, char *content)
{
	t_env	*holder;

	holder = *env;
	while (holder)
	{
		if (ft_strcmp(holder->var, var) == 0)
		{
			if (holder->content)
				free(holder->content);
			if (content)
				holder->content = ft_strdup(content);
			else
				holder->content = NULL;
			return ;
		}
		holder = holder->next;
	}
	if (content)
		ft_env_lstadd_back(env, ft_env_lstnew(ft_strdup(var),
				ft_strdup(content)));
	else
		ft_env_lstadd_back(env, ft_env_lstnew(ft_strdup(var), NULL));
}

char	*ft_getenv(t_env *env, char *var)
{
	while (env)
	{
		if (ft_strcmp(env->var, var) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
