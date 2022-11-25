/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:45:12 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/24 15:54:36 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		gvar.exit = 1;
	}
}
