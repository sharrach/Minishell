/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:23:24 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/06 12:49:57 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_echo(char **arg)
{
	int i;
	
	i = 1;
	while (ft_strcmp(arg[i], "-n") == 0)
		i++;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i ++;
	}
	if (ft_strcmp(arg[1], "-n"))
		printf("\n");
	return (0);
}
