/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:45:12 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 18:10:30 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		if (g_var.here_doc)
		{
			g_var.here_doc = 0;
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_redisplay();
			g_var.exit = 130;
		}
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_var.exit = 1;
		}
	}
}
