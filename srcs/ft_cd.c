/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:48:38 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 17:54:21 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char **args, t_env **env)
{
	char		*path;
	char		new_path[PATH_MAX];
	char		old_path[PATH_MAX];
	char		*pwd;
	static int	i[2];

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
	if (ft_getenv(*env, "PWD"))
		i[1] = 1;
	if (!ft_getenv(*env, "PWD") && i[1] == 1)
		i[1]++;
	if (ft_getenv(*env, "PWD"))
		ft_setenv(env, "OLDPWD", ft_getenv(*env, "PWD"));
	else if ((!ft_getenv(*env, "PWD") && ft_getenv(*env, "OLDPWD") && i[0] == 0) || (i[1] == 2))
	{
		ft_setenv(env, "OLDPWD", NULL);
		i[0] = 1;
		i[1] = 0;
	}
	else if (!ft_getenv(*env, "PWD"))
		ft_setenv(env, "OLDPWD", getcwd(old_path, PATH_MAX));
	if (chdir(path) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2), perror(path), 1);
	if (getcwd(new_path, PATH_MAX) == NULL && errno == ENOENT)
	{
		pwd = ft_getenv(*env, "PWD");
		if (ft_strcmp(args[1], ".") == 0)
			ft_setenv(env, "PWD", ft_strjoin(pwd, "/."));
		else if (ft_strcmp(args[1], "..") == 0)
			ft_setenv(env, "PWD", ft_strjoin(pwd, "/.."));
		return (perror("minishell: chdir: error retrieving current directory: "
				"getcwd: cannot access parent directories"), 0);
	}
	if ((args[1] && ft_strcmp(args[1], "-") == 0))
		ft_putendl_fd(path, STDOUT_FILENO);
	if (ft_getenv(*env, "PWD"))
		ft_setenv(env, "PWD", new_path);
	return (EXIT_SUCCESS);
}
