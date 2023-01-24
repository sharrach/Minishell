/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:06:26 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/22 20:46:53 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**get_paths(t_env *env)
{
	char	**paths;
	char	*path;

	path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

int	ft_get_cmd_path(char **cmd, t_env *env)
{
	char	**paths;
	char	*path;
	char	*add_slash;
	int		i;

	paths = get_paths(env);
	if (!paths)
		return (ft_perr(cmd[0], "No such file or directory"), exit(127), 0);
	i = 0;
	while (paths[++i])
	{
		add_slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(add_slash, *cmd);
		free(add_slash);
		if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
			return (free_2d(paths), ft_perr(cmd[0], "Permission denied"),
				exit(126), 0);
		else if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (free_2d(paths), free(*cmd), *cmd = path, 1);
		free(path);
	}
	free_2d(paths);
	if (ft_strchr(cmd[0], '/') && chdir(cmd[0]) == -1)
		return (ft_perr(cmd[0], "No such file or directory"), exit(127), 0);
	return (ft_perr(cmd[0], "command not found"), exit(127), 0);
}
