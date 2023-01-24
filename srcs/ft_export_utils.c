/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:47:32 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/23 12:51:22 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap(t_env **env)
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

void	check_content(t_env	*holder)
{
	while (holder)
	{
		if (holder->content)
			printf("declare -x %s=\"%s\"\n", holder->var, holder->content);
		else
			printf("declare -x %s\n", holder->var);
		holder = holder->next;
	}
}
