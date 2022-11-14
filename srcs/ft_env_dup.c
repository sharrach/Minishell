/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:50:09 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/12 17:36:308 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_varlen(char *str)
{
	size_t	i; 

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			break ;
		i++;
	}
	return (i);
}

void	ft_duplicate_env(t_vars *vars, char **env)
{
	int		i;
	int		varlen;
	char	*var;
	char	*content;

	vars->env = NULL;
	i = 0;
	while (env[i])
	{
		varlen = ft_varlen(env[i]);
		var = ft_substr(env[i], 0, varlen);
		if (ft_strchr(env[i], '='))
			varlen += 1;
		content = ft_substr(env[i], varlen, ft_strlen(env[i]) - varlen);
		ft_env_lstadd_back(&vars->env, ft_env_lstnew(var, content));
		i++;
	}
}

t_env	*ft_duplicate_export(t_env *env)
{
	char	*var;
	char	*content;
	t_env	*env_dup;

	env_dup = NULL;
	while (env)
	{
		var = ft_strdup(env->var);
		if (env->content)
			content = ft_strdup(env->content);
		else
			content = NULL;
		ft_env_lstadd_back(&env_dup, ft_env_lstnew(var, content));
		env = env->next;
	}
	return (env_dup);
}
