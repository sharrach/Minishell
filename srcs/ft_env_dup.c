/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:50:09 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/09 19:28:35 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_varlen(char *str)
{
	size_t	i; 

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
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
