/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:48:38 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/20 11:22:11 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	old_path[PATH_MAX];
	char	new_path[PATH_MAX];

	if (ft_arrlen(args) > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	path = args[1];
	if (ft_arrlen(args) == 1 || (args[1] && ft_strcmp(args[1], "--") == 0))
		path = ft_getenv(*env, "HOME");
	if (!path)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	if ((args[1] && ft_strcmp(args[1], "-") == 0))
		path = ft_getenv(*env, "OLDPWD");
	if (!path)
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
	getcwd(old_path, PATH_MAX);
	if (chdir(path) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2), perror(path), 1);
	ft_setenv(env, "OLDPWD", old_path);
	getcwd(new_path, PATH_MAX);
	ft_setenv(env, "PWD", new_path);
	return (0);
}
