/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:45:12 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 18:55:14 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_signals(int sig)
{
    if (sig == 1)
    {
        printf("exit \n");
        exit (0);
    }
    if (sig == 2)
    {
        signal(SIGINT, handle_c);
        signal(SIGINT, handle_slash);
    }
    if (sig == 3)
    {
        signal(SIGINT, display_prompt);
    }
}

void    handle_c(int sig)
{
    g_exit = 1;
    ft_putstr_fd("\n", STDOUT_FILENO);
    (void)sig;

}

void    handle_slash(int sig)
{
    g_exit = 0;
    printf("exit \n");
    (void)sig;
}

void	display_prompt(int sig)
{
	g_exit = 1;
    ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}
