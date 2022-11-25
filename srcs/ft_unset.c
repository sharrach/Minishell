/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:26:26 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/24 16:07:09 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_env_lstdelone(t_env **env)
{
	t_env	*holder;

	holder = *env;
	if ((*env)->prev)
		(*env)->prev->next = (*env)->next;
	if ((*env)->next)
		(*env)->next->prev = (*env)->prev;
	*env = (*env)->next;
	free(holder->var);
	free(holder->content);
	free(holder);
}
// add error not valid indentifier

int	ft_unset(char **args, t_env **env)
{
	t_env	*holder;
	int		is_del;
	int		i;

	holder = *env;
	while (holder)
	{
		is_del = 0;
		i = 1;
		while (args[i])
		{
			if (ft_strcmp(holder->var, args[i]) == 0)
			{
				if (!holder->prev)
					*env = holder->next;
				ft_env_lstdelone(&holder);
				is_del = 1;
				break ;
				i++;
			}
			i++;
		}
		if (!is_del)
			holder = holder->next;
	}
	return (EXIT_SUCCESS);
}
