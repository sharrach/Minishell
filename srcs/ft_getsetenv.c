/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:26:21 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/12 11:30:17 by sharrach         ###   ########.fr       */
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
			{
				// printf("holder->content %s\n",holder->content);
				free(holder->content);
				holder->content = ft_strdup(content);
				// printf("holder->content %s\n",holder->content);
			}
			else
				holder->content = NULL;
			return ;
		}
		holder = holder->next;
	}
	if (content)
		ft_env_lstadd_back(env, ft_env_lstnew(ft_strdup(var), ft_strdup(content)));
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


// "export"
//print env ordered

// "export VAR"
// 1- ila kant VAR maghaydir liha walo
// 2- ila makantch VAR fl env ghadi izidha walakin content = ""

// "export VAR=" || "export VAR=CONTENT"
// ghay9ele 3la VAR o ghadi ibedelha b dakchi li wra '='

// NOTE:
// fach tbghi tprinti env matprintich dakchi li mafihch content
// 