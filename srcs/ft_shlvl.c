/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:34:31 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/25 11:55:20 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_new_pwd(t_env *env)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		ft_setenv(&env, "PWD", pwd);
}

void	ft_shlvl_increment(t_env *env)
{
	char	*content;
	int		value;

	content = ft_getenv(env, "SHLVL");
	if (content)
	{
		value = ft_atoi(content) + 1;
		if (value < 0)
			value = 0;
		content = ft_itoa(value);
	}
	else
		content = ft_strdup("1");
	ft_setenv(&env, "SHLVL", content);
	free(content);
	ft_unset_var("OLDPWD", &env);
	ft_new_pwd(env);
}
