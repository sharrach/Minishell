/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:56:47 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/12 11:45:59 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_export_arg(char **args, t_env **env)
{
	char    *tmps;
	int		i;
	int		j;

	tmps = ft_strdup("");
	i = 1;
	while(args[i])
	{
		j = 0;
		if (args[i][0] >= '0' && args[i][0] <= '9')
		{
			i++;
			continue;
		}
		while (args[i][j] != '=')
		{
			tmps[j] = args[i][j];
			j++;
		}
		tmps[j] = '\0';
		ft_setenv(env, tmps, (ft_strchr(args[i], '=') + 1));
		i++;
	}
}

void	ft_export(char **args, t_env **env)
{
	while(env)
	{
		
		env = env->next;
	}
}
