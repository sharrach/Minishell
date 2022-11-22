/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:36:50 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/22 21:16:07 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_vars	vars;
	t_lst	*tokens;

	(void)ac;
	(void)av;
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, ft_handle_signals);
	ft_duplicate_env(&vars, env);
	while (1)
	{
		vars.input = readline("Tzz-shell> ");
		if (!vars.input)
			continue ;
		add_history(vars.input);
		tokens = ft_tokenization(vars.input);
		if (!tokens)
			continue ;
		if (syntax_error(tokens))
		{
			printf("Syntax error\n");
			continue ;
		}
		vars.cmds = ft_parsing(tokens);
		ft_exec_commands(&vars);
	}
	return (0);
}
