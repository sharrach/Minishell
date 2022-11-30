/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:40:16 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/30 12:28:06 by sharrach         ###   ########.fr       */
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
			if (pipe(p) == -1)
				return ;
			cmds->pipe[STDOUT_FILENO] = p[STDOUT_FILENO];
			cmds->next->pipe[STDIN_FILENO] = p[STDIN_FILENO];
		}
		cmds = cmds->next;
	}
}

void	ft_close_pipes(t_mini *cmd)
{
	if (cmd->pipe[STDIN_FILENO] != STDIN_FILENO)
	{
		close(cmd->pipe[STDIN_FILENO]);
		cmd->pipe[STDIN_FILENO] = STDIN_FILENO;
	}
	if (cmd->pipe[STDOUT_FILENO] != STDOUT_FILENO)
	{
		close(cmd->pipe[STDOUT_FILENO]);
		cmd->pipe[STDOUT_FILENO] = STDOUT_FILENO;
	}
	if (cmd->red[STDIN_FILENO] != STDIN_FILENO)
	{
		close(cmd->red[STDIN_FILENO]);
		cmd->red[STDIN_FILENO] = STDIN_FILENO;
	}
	if (cmd->red[STDOUT_FILENO] != STDOUT_FILENO)
	{
		close(cmd->red[STDOUT_FILENO]);
		cmd->red[STDOUT_FILENO] = STDOUT_FILENO;
	}
}

static void	ft_out_red(t_mini **cmds, t_lst **redir)
{
	t_lst	*t1;
	t_mini	*t2;

	t1 = *redir;
	t2 = *cmds;
	if (t1->type == OUT_RED)
	{
		t2->red[STDOUT_FILENO] =
			open(t1->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (t1->type == OUT_REDD)
	{
		t2->red[STDOUT_FILENO] =
			open(t1->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

void	ft_open_redirs(t_mini *cmds, t_env *env)
{
	t_lst	*redir;

	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			ft_out_red(&cmds, &redir);
			if (redir->type == IN_RED)
			{
				cmds->red[STDIN_FILENO] = open(redir->content, O_RDONLY);
			}
			else if (redir->type == IN_REDD)
			{
				cmds->red[STDIN_FILENO] =
					ft_here_doc(cmds->redir->content, env);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
}
