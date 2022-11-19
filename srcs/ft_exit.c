/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:56:56 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 17:03:31 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isnum(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	printf("exit\n");
	if (args[1])
	{
		if (ft_isnum(args[1]))
		{
			if (ft_arrlen(args) > 2)
			{
				printf("minishell: exit: too many arguments\n");
				return (EXIT_FAILURE);
			}
			g_exit = ft_atoi(args[1]);
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			g_exit = 255;
		}
	}
	return (exit((unsigned char)g_exit), EXIT_SUCCESS);
}
