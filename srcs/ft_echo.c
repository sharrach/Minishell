/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:23:24 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/20 12:13:01 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	ft_newl(char ***arg, int *i, int *nl)
{
	int	j;

	*i = 1;
	j = 1;
	*nl = 1;
	while ((*arg)[*i] && (*arg)[*i][0] == '-')
	{
		j = 1;
		while ((*arg)[*i][j] && (*arg)[*i][j] == 'n')
			j++;
		if (!(*arg)[*i][j])
		{
			*nl = 0;
			(*i)++;
		}
		else
			break ;
	}
}

int	ft_echo(char **arg)
{
	int	i;
	int	nl;

	ft_newl(&arg, &i, &nl);
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i ++;
	}
	if (nl)
		printf("\n");
	return (0);
}
