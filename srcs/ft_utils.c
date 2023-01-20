/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:22:27 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/18 16:11:11 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_alphanum_check(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_varlen(str))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int	ft_expand_varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '?')
			return (1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
		i++;
	}
	return (i);
}
