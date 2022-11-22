/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:06:26 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/22 13:46:13 by sharrach         ###   ########.fr       */
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
	int		i;

	paths = get_paths(env);
	if (!paths)
		return (0);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_stradd(path, *cmd);
		if (!access(path, F_OK) && !access(path, X_OK))
		{
			free_2d(paths);
			free(*cmd);
			*cmd = path;
			return (1);
		}
		free(path);
		i++;
	}
	free_2d(paths);
	return (0);
}
