/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:48:38 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/07 12:37:39 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char	**args, char **env)
{
	char	*path;

	path = args[1];
	if (ft_arrlen(args) == 1 || (ft_arrlen(args) == 2 && args[1] == "--"))
		path = ft_getenv(env, "HOME");
	if (ft_arrlen(args) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(path);
		return (1);
	}
	return (0);
}
