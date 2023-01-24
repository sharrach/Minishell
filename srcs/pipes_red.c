/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:40:16 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 13:15:44 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_open_pipes(t_mini *cmds)
{
	int	p[2];

	while (cmds)
	{
		if (cmds->next)
		{
			if (pipe(p) != -1)
			{
				cmds->pipe[STDOUT_FILENO] = p[STDOUT_FILENO];
				cmds->next->pipe[STDIN_FILENO] = p[STDIN_FILENO];
			}
		}
		cmds = cmds->next;
	}
}

void	ft_close_fds(t_mini **cmd)
{
	if ((*cmd)->pipe[STDIN_FILENO] != STDIN_FILENO)
	{
		close((*cmd)->pipe[STDIN_FILENO]);
		(*cmd)->pipe[STDIN_FILENO] = STDIN_FILENO;
	}
	if ((*cmd)->prev && (*cmd)->prev->pipe[STDOUT_FILENO] != STDOUT_FILENO)
	{
		close((*cmd)->prev->pipe[STDOUT_FILENO]);
		(*cmd)->prev->pipe[STDOUT_FILENO] = STDOUT_FILENO;
	}
	if ((*cmd)->red[STDIN_FILENO] != STDIN_FILENO)
	{
		close((*cmd)->red[STDIN_FILENO]);
		(*cmd)->red[STDIN_FILENO] = STDIN_FILENO;
	}
	if ((*cmd)->red[STDOUT_FILENO] != STDOUT_FILENO)
	{
		close((*cmd)->red[STDOUT_FILENO]);
		(*cmd)->red[STDOUT_FILENO] = STDOUT_FILENO;
	}
}

static void	ft_out_red(t_mini **cmd, t_lst *redir, t_env *env)
{
	if ((redir->type == OUT_RED || redir->type == OUT_REDD)
		&& (*cmd)->red[STDOUT_FILENO] != STDOUT_FILENO)
		close((*cmd)->red[STDOUT_FILENO]);
	if (redir->type == OUT_RED)
	{
		ft_expand_str(&redir->content, env, 0, 0);
		ft_remove_quotes_str(&redir->content);
		(*cmd)->red[STDOUT_FILENO]
			= open(redir->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (redir->type == OUT_REDD)
	{
		ft_expand_str(&redir->content, env, 0, 0);
		ft_remove_quotes_str(&redir->content);
		(*cmd)->red[STDOUT_FILENO]
			= open(redir->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

int	ft_open_redirs(t_mini *cmds, t_env *env)
{
	t_lst	*redir;

	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			ft_out_red(&cmds, redir, env);
			if ((redir->type == IN_RED || redir->type == IN_REDD)
				&& cmds->red[STDIN_FILENO] != STDIN_FILENO)
				close(cmds->red[STDIN_FILENO]);
			if (redir->type == IN_RED)
			{
				ft_expand_str(&redir->content, env, 0, 0);
				ft_remove_quotes_str(&redir->content);
				cmds->red[STDIN_FILENO] = open(redir->content, O_RDONLY);
			}
			else if (!ft_open_heredoc(&cmds, env, &redir))
				return (0);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (1);
}

void	ft_close_all_fds(t_mini *cmds)
{
	while (cmds)
	{
		if (cmds->pipe[STDIN_FILENO] != STDIN_FILENO)
			close(cmds->pipe[STDIN_FILENO]);
		if (cmds->pipe[STDOUT_FILENO] != STDOUT_FILENO)
			close(cmds->pipe[STDOUT_FILENO]);
		if (cmds->red[STDIN_FILENO] != STDIN_FILENO)
			close(cmds->red[STDIN_FILENO]);
		if (cmds->red[STDOUT_FILENO] != STDOUT_FILENO)
			close(cmds->red[STDOUT_FILENO]);
		cmds = cmds->next;
	}
}
