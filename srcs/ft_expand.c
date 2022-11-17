/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:14:04 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/17 19:24:40 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_expand_varlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
				return (i);
		i++;
	}
	return (i);
}

void	ft_expand_str(char **str, t_env *env)
{
	int		i;
	int		len;
	char	*new_str;
	char	*var;
	int		quote;

	new_str = ft_strdup("");
	len = 0;
	i = 0;
	quote = 0;
	while ((*str)[i])
	{
		if (!quote && ((*str)[i] == '\'' || (*str)[i] == '"'))
			quote = (*str)[i];
		else if (quote && (*str)[i] == quote)
			quote = 0;
		if ((*str)[i] == '$' && (!quote || quote == '"'))
		{
			new_str = ft_stradd(new_str, ft_substr((*str), i - len, len));
			var = ft_substr((*str), i + 1, ft_expand_varlen(&(*str)[i + 1]));
			if (ft_getenv(env, var))
				new_str = ft_stradd(new_str, ft_getenv(env, var));
			free(var);
			len = 0;
			i += ft_expand_varlen(&(*str)[i + 1]) + 1;
		}
		len++;
		i++;
	}
	new_str = ft_stradd(new_str, ft_substr((*str), i - len, len));
	free(*str);
	*str = new_str;
}

void	ft_expand(char **cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_expand_str(&cmd[i], env);
		i++;
	}
}
