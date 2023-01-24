/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:36:50 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 17:54:33 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_gvar	g_var;

static void	ft_readline(t_vars vars)
{
	t_lst	*tokens;

	while (1)
	{
		vars.input = readline("mini-shell> ");
		if (!vars.input)
			break ;
		if (vars.input[0])
			add_history(vars.input);
		tokens = ft_tokenization(vars.input);
		if (!tokens)
			continue ;
		if (ft_syntax_error(tokens))
		{
			printf("Syntax error\n");
			continue ;
		}
		ft_parsing(&vars, tokens);
		ft_lst_lstclear(&tokens);
		ft_exec_commands(&vars);
		ft_mini_lstclear(&vars.cmds);
	}
}

int	main(int ac, char *av[], char *env[])
{
	t_vars	vars;

	(void)ac;
	(void)av;
	vars.act.sa_handler = &ft_handle_signals;
	sigaction(SIGINT, &vars.act, NULL);
	signal(SIGQUIT, SIG_IGN);
	ft_duplicate_env(&vars, env);
	ft_shlvl_increment(vars.env);
	ft_readline(vars);
	return (0);
}
