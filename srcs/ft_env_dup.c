/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:50:09 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/04 09:50:28 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_duplicate_env(t_vars *vars, char **env)
{
	int	i;

	vars->env = ft_calloc(ft_arrlen(env) + 1, sizeof(char *));
	if (!vars->env)
		return ;
	i = 0;
	while(env[i])
	{
		vars->env[i] = ft_strdup(env[i]);
		i++;
	}
}
