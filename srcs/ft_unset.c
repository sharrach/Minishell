/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:26:26 by sharrach          #+#    #+#             */
/*   Updated: 2022/12/21 14:09:41 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_alphanum_check2(char *str)
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

void	ft_unset_var(char *arg, t_env **env)
{
	t_env	*holder;
	
	holder = *env;
	while (holder)
	{
		if (ft_strcmp(holder->var, arg) == 0)
		{
			if (!holder->prev)
				*env = holder->next;
			ft_env_lstdelone(&holder);
			break ;
		}
		holder = holder->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int	exit_status;
	int	i;

	exit_status = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (ft_isdigit(args[i][0]) || !ft_alphanum_check2(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			exit_status = EXIT_FAILURE;
			i++;
			continue ;
		}
		ft_unset_var(args[i], env);
		i++;
	}
	return (exit_status);
}
