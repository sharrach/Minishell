/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:06:26 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/01 17:22:17 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char    **get_paths(char *env[])
{
    char    **paths;
    int     i;

    i = 0;
    while(env[i] && ft_strncmp(env[i], "PATH=", 5))
        i++;
    if (!env[i])
        return (NULL);
    paths = ft_split(env[i] + 5, ':');
    return (paths);
}

int ft_get_cmd_path(char **cmd, char *env[])
{
    char    **paths;
    char    *path;
    char    *add_slash;
    int     i;

    paths = get_paths(env);
    if (!paths)
        return (0);
    i = 0;
    while(paths[i])
    {
        add_slash = ft_strjoin(paths[i], "/");
        path = ft_strjoin(add_slash, *cmd);
        free(add_slash);
        if(!access(path, F_OK) && !access(path, X_OK))
        {
            free_2d(paths);
            free(*cmd);
            return (*cmd = path, 1);
        }
        i++;
        free(path);
    }
    free_2d(paths);
    return (0);
}
