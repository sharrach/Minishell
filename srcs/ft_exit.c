/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:56:56 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/25 11:55:52 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static long double	ft_datoi(const char *str)
{
	int			i;
	int			sign;
	long double	nb;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + str[i] - 48;
		i++;
	}
	return (sign * nb);
}

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
				return (printf("minishell: exit: too many arguments\n"), 1);
			if (ft_datoi(args[1]) > LLONG_MAX || ft_datoi(args[1]) < LLONG_MIN)
			{
				printf("minishell: exit: %s: numeric argument required\n",
					args[1]);
				g_var.exit = 255;
			}
			else
				g_var.exit = (unsigned char)ft_atoi(args[1]);
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			g_var.exit = 255;
		}
	}
	exit ((unsigned char)g_var.exit);
}
