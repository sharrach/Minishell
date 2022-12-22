/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:36:50 by sharrach          #+#    #+#             */
/*   Updated: 2022/12/22 13:00:07 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_gvar	gvar;

int	main(int ac, char *av[], char *env[])
{
	t_vars	vars;
	t_lst	*tokens;

	(void)ac;
	(void)av;
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, SIG_IGN);
	ft_duplicate_env(&vars, env);
	ft_shlvl_increment(vars.env);
	while (1)
	{
		vars.input = readline("Tzz-shell> ");
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
		vars.cmds = ft_parsing(tokens);
		ft_lst_lstclear(&tokens);
		ft_exec_commands(&vars);
		ft_mini_lstclear(&vars.cmds);
	}
	return (0);
}
