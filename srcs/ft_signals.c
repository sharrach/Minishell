/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:45:12 by sharrach          #+#    #+#             */
/*   Updated: 2022/12/15 18:48:21 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		if (gvar.here_doc)
		{
			gvar.here_doc = 0;
			ft_putstr_fd("\n", STDOUT_FILENO);
			// rl_replace_line("", 0);
			// rl_on_new_line();
			rl_redisplay();
			gvar.exit = 130;
		}
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			gvar.exit = 1;
		}
	}
}
