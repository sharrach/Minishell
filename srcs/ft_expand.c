/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:14:04 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 13:17:40 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_quote(int *quote, char *str, int i)
{
	if (!*quote && (str[i] == '\'' || str[i] == '"'))
		*quote = str[i];
	else if (*quote && str[i] == *quote)
		*quote = 0;
}

static void	ft_return(char **new_str, int *i, int *len, char **str)
{
	*new_str = ft_stradd2(*new_str, ft_substr((*str), *i - *len, *len));
	free(*str);
	*str = *new_str;
}

void	ft_expand_str(char **str, t_env *env, int quote, int len)
{
	char	*new_str;
	char	*var;
	int		i;

	new_str = ft_strdup("");
	i = -1;
	while ((*str)[++i])
	{
		ft_quote(&quote, *str, i);
		if ((*str)[i] == '$' && (ft_isalpha((*str)[i + 1])
			|| ft_strchr("_?", (*str)[i + 1])) && (!quote || quote == '"'))
		{
			new_str = ft_stradd2(new_str, ft_substr((*str), i - len, len));
			var = ft_substr(*str, i + 1, ft_expand_varlen(&(*str)[i + 1]));
			if (ft_strcmp(var, "?") == 0)
				new_str = ft_stradd2(new_str, ft_itoa(g_var.exit));
			else if (ft_getenv(env, var))
				new_str = ft_stradd(new_str, ft_getenv(env, var));
			free(var);
			len = -1;
			i += ft_expand_varlen(&(*str)[i + 1]);
		}
		len++;
	}
	ft_return(&new_str, &i, &len, str);
}

void	ft_expand(char **cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_expand_str(&cmd[i], env, 0, 0);
		i++;
	}
}
