/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:49:03 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 15:40:43 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->content)
			printf("%s=%s\n", env->var, env->content);
		env = env->next;
	}
	return (0);
}
