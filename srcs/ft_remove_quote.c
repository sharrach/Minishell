/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:19:23 by iellyass          #+#    #+#             */
/*   Updated: 2022/11/24 17:45:05 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_quote_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static void	ft_remove(char **str)
{
	char	*new_str;
	int		len;
	int		i;

	new_str = ft_strdup("");
	len = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			new_str = ft_stradd2(new_str, ft_substr((*str), i - len, len));
			new_str = ft_stradd2(new_str,
				ft_substr(*str, i + 1, ft_quote_len(&(*str)[i + 1], (*str)[i])));
			len = -1;
			i += ft_quote_len(&(*str)[i + 1], (*str)[i]);
		}
		len++;
		i++;
	}
	new_str = ft_stradd2(new_str, ft_substr((*str), i - len, len));
	free(*str);
	*str = new_str;
}

void	ft_remove_quote(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_remove(&cmd[i]);
		i++;
	}
}
