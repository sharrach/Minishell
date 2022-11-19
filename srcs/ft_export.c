/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:56:47 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 15:59:23 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_swap(t_env **env)
{
	char	*tmp_var;
	char	*tmp_content;

	tmp_var = (*env)->var;
	tmp_content = (*env)->content;
	(*env)->var = (*env)->next->var;
	(*env)->content = (*env)->next->content;
	(*env)->next->var = tmp_var;
	(*env)->next->content = tmp_content;
}

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
			if (holder2->next && ft_strcmp(holder2->var, holder2->next->var) > 0)
				ft_swap(&holder2);
			holder2 = holder2->next;
		}
		holder = holder->next;
	}
	holder = head;
	while (holder)
	{
		if (holder->content)
			printf("declare -x %s=\"%s\"\n", holder->var, holder->content);
		else
			printf("declare -x %s\n", holder->var);
		holder = holder->next;
	}
	ft_env_lstclear(&head);
}

static int	ft_alphanum_check(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_varlen(str))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
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
		if ((args[i][0] >= '0' && args[i][0] <= '9') || !ft_alphanum_check(args[i]))
		{
			printf("misihell: export: `%s': not a valid identifier\n", args[i++]);
			continue;
		}
		var = ft_substr(args[i], 0, ft_varlen(args[i]));
		content = NULL;
		if (args[i][ft_varlen(args[i])] == '=')
			content = ft_substr(args[i], ft_varlen(args[i]) + 1, ft_strlen(args[i]) - (ft_varlen(args[i]) + 1));
		else if (args[i][ft_varlen(args[i])] == '+'
			&& args[i][ft_varlen(args[i]) + 1] == '=')
		{
			if (ft_getenv(*env, var))
				content = ft_strjoin(ft_getenv(*env, var), &args[i][ft_varlen(args[i]) + 2]);
			else
				content = ft_strdup(&args[i][ft_varlen(args[i]) + 2]);
		}
		ft_setenv(env, var, content);
		free(var);
		free(content);
		i++;
	}
	return (EXIT_SUCCESS);
}
