/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:36:50 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/01 17:29:04 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error(t_lst	*tokens)
{
	if (tokens->type == PIPE)
		return (1);
	while(tokens)
	{
		if (tokens->type != WORD
			&& (!tokens->next || (tokens->next && tokens->next->type != WORD)))
			return (1);
		if (tokens->type == QUOTE || tokens->type == DB_QUOTE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	ft_token_type(char *content)
{
	int	type;

	if (!strcmp(content, "|"))
		type = PIPE;
	else if (!strcmp(content, "<"))
		type = IN_RED;
	else if (!strcmp(content, ">"))
		type = OUT_RED;
	else if (!strcmp(content, "<<"))
		type = IN_REDD;
	else if (!strcmp(content, ">>"))
		type = OUT_REDD;
	else if (!strcmp(content, "\""))
		type = DB_QUOTE;
	else if (!strcmp(content, "'"))
		type = QUOTE;
	else
		type = WORD;
	return (type);
}

t_lst	*ft_tokenization(char *input)
{
	t_lst	*tokens;
	char	*content;
	int		type;
	int 	i;
	int		size;

	tokens = NULL;
	i = 0;
	while(input[i])
	{
		if (input[i] == ' ')
		{
			i ++;
			continue ;
		}
		size = 0;
		if ((input[i + size] == '>' && input[i + size + 1] == '>')
				|| (input[i + size] == '<' && input[i + size + 1] == '<'))
			size += 2;
		else if (ft_strchr("|<>" ,input[i + size]))
			size++;
		else
		{
			while (input[i + size] && !ft_strchr("| <>" , input[i + size]))
			{
				if ((input[i + size] == '"' || input[i + size] == '\'')
					&& input[i + size + 1] && ft_strchr(&input[i + size + 1] , input[i + size]))
					size = ft_strlen(input) - ft_strlen(ft_strchr(&input[i + size + 1] , input[i + size]));
				else if (input[i + size] == '"' || input[i + size] == '\'')
					break;
				size++;
			}
		}
		if (size == 0 && input[i] == input[i + size])
			size = 1;
		content = ft_substr(input, i, size);
		type = ft_token_type(content);
		ft_lst_lstadd_back(&tokens, ft_lst_lstnew(content, type));
		i += size;
	}
	return (tokens);
}

static  void handle_signals(int signo) {
	if (signo == SIGINT) {
		printf("You pressed Ctrl+C\n");
	}
}

t_mini	*ft_parsing(t_lst *tokens)
{
	t_mini	*cmds;
	t_lst	*redir;
	char	**cmd;
	int		w_count;
	int 	i;
	t_lst	*tmp;

	cmds = NULL;
	redir = NULL;
	w_count = 0;
	i = 0;
	tmp = tokens;
	while(tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && (tmp->prev == NULL
			|| (tmp->prev->type != IN_RED && tmp->prev->type != OUT_RED
				&& tmp->prev->type != IN_REDD && tmp->prev->type != OUT_REDD)))
			w_count++;
		tmp = tmp->next;
	}
	cmd = (char **)ft_calloc(w_count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == WORD && (tokens->prev == NULL
			|| (tokens->prev->type != IN_RED && tokens->prev->type != OUT_RED
				&& tokens->prev->type != IN_REDD && tokens->prev->type != OUT_REDD)))
			cmd[i++] = tokens->content;
		if (tokens->type == PIPE || !tokens->next)
		{
			ft_mini_lstadd_back(&cmds, ft_mini_lstnew(cmd, redir));
			redir = NULL;
		}
		if (tokens->type == IN_RED || tokens->type == OUT_RED
			|| tokens->type == IN_REDD || tokens->type == OUT_REDD)
		{
			ft_lst_lstadd_back(&redir, ft_lst_lstnew(tokens->next->content, tokens->type));
		}
		if (tokens->type == PIPE && tokens->next)
		{
			w_count = 0;
			i = 0;
			tmp = tokens;
			while(tmp && tmp->type != PIPE)
			{
				if (tmp->type == WORD && (tmp->prev == NULL
					|| (tmp->prev->type != IN_RED && tmp->prev->type != OUT_RED
						&& tmp->prev->type != IN_REDD && tmp->prev->type != OUT_REDD)))
					w_count++;
				tmp = tmp->next;
			}
			cmd = (char **)ft_calloc(w_count + 1, sizeof(char *));
			if (!cmd)
				return (NULL);
		}
		tokens = tokens->next;
	}
	return (cmds);
}

void	ft_exec_command(t_mini *cmds, char *env[])
{
	pid_t	pid;

	ft_open_pipes(cmds);
	ft_open_redirs(cmds);
	while(cmds)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			if (cmds->pipe[STDIN_FILENO] != STDIN_FILENO)
			{
				dup2(cmds->pipe[STDIN_FILENO], STDIN_FILENO);
				close(cmds->pipe[STDIN_FILENO]);
			}
			if (cmds->pipe[STDOUT_FILENO] != STDOUT_FILENO)
			{
				dup2(cmds->pipe[STDOUT_FILENO], STDOUT_FILENO);
				close(cmds->pipe[STDOUT_FILENO]);
			}
			if (!ft_get_cmd_path(&cmds->cmd[0], env))
			{
				printf("%s: command not found\n", cmds->cmd[0]);
				return ;
			}
			execve(cmds->cmd[0], cmds->cmd, env);
		}
		cmds = cmds->next;
	}
	waitpid(pid, NULL, 0);
	write(2, "123\n", 4);
}

int main (int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	t_lst *tokens;
	t_mini	*cmds;
	char *input;
	char *shell_prompt = "Tzz-shell> ";

	signal(SIGINT, handle_signals);
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	while (1)
	{
		input = readline(shell_prompt);
		if (!input)
			break;
		add_history(input);
		tokens = ft_tokenization(input);
		if (!tokens)
			break;
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
			continue;
		}
		cmds = ft_parsing(tokens);
		//////////////////////
		// t_mini *tmp_cmds = cmds;
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
		ft_exec_command(cmds, env);
		
	}
	return 0;
}