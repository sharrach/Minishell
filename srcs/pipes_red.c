/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:40:16 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 16:02:01 by sharrach         ###   ########.fr       */
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

void	ft_close_pipes(t_mini *cmds)
{
	while (cmds)
	{
		if (cmds->next)
		{
			close(cmds->pipe[STDOUT_FILENO]);
			close(cmds->next->pipe[STDIN_FILENO]);
		}
		cmds = cmds->next;
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
			if (redir->type == OUT_RED)
			{
				if (cmds->pipe[STDOUT_FILENO] != STDOUT_FILENO)
					close(cmds->pipe[STDOUT_FILENO]);
				cmds->pipe[STDOUT_FILENO] = open(redir->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			}
			else if (redir->type == OUT_REDD)
			{
				if (cmds->pipe[STDOUT_FILENO] != STDOUT_FILENO)
					close(cmds->pipe[STDOUT_FILENO]);
				cmds->pipe[STDOUT_FILENO] = open(redir->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
			}
			else if (redir->type == IN_RED)
			{
				if (cmds->pipe[STDIN_FILENO] != STDIN_FILENO)
					close(cmds->pipe[STDIN_FILENO]);
				cmds->pipe[STDIN_FILENO] = open(redir->content, O_RDONLY);
			}
			else if (redir->type == IN_REDD)
				cmds->pipe[STDIN_FILENO] = ft_here_doc(cmds->redir->content, env);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
}
