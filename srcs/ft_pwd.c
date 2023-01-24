/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:47:46 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/23 12:54:22 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == NULL && errno == ENOENT)
	{
		return (perror("minishell: pwd: error retrieving current directory: "
				"getcwd: cannot access parent directories"), 0);
	}
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
