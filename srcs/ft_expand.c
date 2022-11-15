/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:14:04 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/15 19:57:59 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_alphanum_check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check(char *str)
{
	size_t	i;

	i = 1;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

void	ft_expand(char **cmd, t_env *env)
{
	char	*path;
	char	*rest;
	char	*var;
	int     i;
	int     len;
	char	*str;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			len = ft_strlen(cmd[i]) - ft_strlen(ft_strchr(cmd[i], '$'));
			if (ft_alphanum_check(ft_strchr(cmd[i], '$') + 1))
			{
				// printf("DKHLAT\n");
				// printf("%s\n", ft_strchr(cmd[i], '$') + 1);
				while (env)
				{
					// printf("DKHLAT2\n");
					if (ft_strcmp(env->var, ft_strchr(cmd[i], '$') + 1) == 0)
					{ 
						path = ft_getenv(env, ft_strchr(cmd[i], '$') + 1);
						str = ft_substr(cmd[i], 0, len);
						// printf("%s%s\n", str,path);
					}
					env = env->next;
				}
			}
			else
			{
				len = (ft_check(ft_strchr(cmd[i], '$') + 1));
				// printf("len: %d\n", len);
				var = ft_substr((ft_strchr(cmd[i], '$') + 1), 0, len);
				// printf("var: %s\n", var);
				rest = ft_substr(ft_strchr(cmd[i], '$') + 1, len,
					ft_strlen(cmd[i]) - ft_strlen(ft_strchr(cmd[i], '$')));
				// printf("rest: %s\n", rest);
				path = ft_getenv(env, var);
				// printf("path: %s\n", path);
				str = ft_substr(cmd[i], 0, ft_strlen(cmd[i]) - ft_strlen(ft_strchr(cmd[i], '$')));
				// printf("DKHLAaaaaaaaaaaaaaT\n");
				// printf("cmd[i]: %s\n", cmd[i]);
				// printf("ft_strchr(cmd[i], '$') + 1): %s\n", ft_strchr(cmd[i], '$') + 1);
				// printf("str: %s\n", str);
				// printf("%s%s%s\n", str,path,rest);
				// printf("DKHLAT\n");
				// printf("%s%s\n\n\n\n\n\n\n", str,path);
				// printf("%d\n",len);
			}
		}
		i++;
	}
}
