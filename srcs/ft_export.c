/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:56:47 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/23 12:51:10 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_export_print(t_env **env)
{
	t_env	*head;
	t_env	*holder;
	t_env	*holder2;

	head = ft_duplicate_export(*env);
	holder = head;
	while (holder)
	{
		holder2 = head;
		while (holder2)
		{
			if (holder2->next
				&& ft_strcmp(holder2->var, holder2->next->var) > 0)
				ft_swap(&holder2);
			holder2 = holder2->next;
		}
		holder = holder->next;
	}
	holder = head;
	check_content(holder);
	ft_env_lstclear(&head);
}

static int	print_error(char str, char *str2)
{
	if (ft_isdigit(str) || !ft_alphanum_check(str2))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static char	*ft_get_content(t_env **env, char *var, char *arg)
{
	char	*content;

	if (arg[ft_varlen(arg)] == '=')
		content = ft_substr(arg, ft_varlen(arg) + 1,
				ft_strlen(arg) - (ft_varlen(arg) + 1));
	else if (arg[ft_varlen(arg)]
		== '+' && arg[ft_varlen(arg) + 1] == '=')
	{
		if (ft_getenv(*env, var))
			content = ft_strjoin
				(ft_getenv(*env, var), &arg[ft_varlen(arg) + 2]);
		else
			content = ft_strdup(&arg[ft_varlen(arg) + 2]);
	}
	else
		content = NULL;
	return (content);
}

int	ft_export(char **args, t_env **env)
{
	int		i;
	char	*var;
	char	*content;

	if (ft_arrlen(args) == 1)
		return (ft_export_print(env), EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		if (print_error(args[i][0], args[i]) == 1)
		{
			i++;
			continue ;
		}
		var = ft_substr(args[i], 0, ft_varlen(args[i]));
		content = ft_get_content(env, var, args[i]);
		ft_setenv(env, var, content);
		free(var);
		free(content);
		i++;
	}
	return (EXIT_SUCCESS);
}
