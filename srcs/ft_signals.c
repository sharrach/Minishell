/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:45:12 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/22 21:16:05 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_signals(int signo)
{
	if (signo == SIGQUIT)
	{
		rl_redisplay();
	}
	if (signo == SIGINT)
	{	
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handle_child_signals(int signo)
{
	
	if (signo == SIGQUIT)
	{
		rl_redisplay();
	}
	if (signo == SIGINT)
	{	
		signal(SIGINT, SIG_IGN);
		printf("hhh\n");
	}
}
