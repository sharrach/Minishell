/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:36:50 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/21 16:50:21 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	handle_signals(int signo)
{
	if (signo == SIGQUIT)
	{
		rl_clear_signals();
		rl_redisplay();
		rl_clear_signals();
	}
	if (signo == SIGINT)
	{	

		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_clear_signals();
		rl_redisplay();
	}
	// printf("Youuuuuuuuuu pressed Ctrl+C\n");
	// // g_exit = 1;
	
	// ft_putstr_fd("\n", STDOUT_FILENO);
	// printf("Youuuuuuuuuu pressed Ctrl+C\n");
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_on_new_line_with_prompt();
	// printf("Youuuuuuuuuu pressed Ctrl+C\n");
	// (void)signo;
}

int	main(int ac, char *av[], char *env[])
{
	t_vars	vars;
	t_lst	*tokens;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	ft_duplicate_env(&vars, env);
	while (1)
	{
		vars.input = readline("Tzz-shell> ");
		if (!vars.input)
			break ;
		add_history(vars.input);
		tokens = ft_tokenization(vars.input);
		if (!tokens)
			break ;
		//////////////////////
		// t_lst *tmp = tokens;
		// while (tmp != NULL)
		// {
		// 	printf("content: '%s'\n", tmp->content);
		// 	printf("type: %d\n\n", tmp->type);
		// 	tmp = tmp->next;
		// }
		//////////////////////
		if (syntax_error(tokens))
		{
			printf("Syntax error\n");
			continue ;
		}
		vars.cmds = ft_parsing(tokens);
		//////////////////////
		// t_mini *tmp_cmds = vars.cmds;
		// while (tmp_cmds)
		// {
		// 	int i = 0;
		// 	while (tmp_cmds->cmd[i])
		// 	{
		// 		printf("%d %s\n", i, tmp_cmds->cmd[i]);
		// 		i++;
		// 	}
		// 	while (tmp_cmds->redir)
		// 	{
		// 		printf("redir: %d - %s\n", tmp_cmds->redir->type, tmp_cmds->redir->content);
		// 		tmp_cmds->redir = tmp_cmds->redir->next;
		// 	}
		// 	printf("\n");
		// 	tmp_cmds = tmp_cmds->next;
		// }
		////////////////////
		ft_exec_commands(&vars);
	}
	return (0);
}
