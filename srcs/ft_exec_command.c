/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:11:16 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/07 10:35:09 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_dup_fds(t_mini *cmds)
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
}

void	ft_exec_command(t_vars *vars, t_mini *cmds)
{
	if (ft_strcmp(cmds->cmd[0], "env") == 0)
		ft_env(vars->env);
	else if (ft_strcmp(cmds->cmd[0], "echo") == 0)
		ft_echo(cmds->cmd);
	else if (ft_strcmp(cmds->cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->cmd[0], "cd") == 0)
		ft_cd(cmds->cmd, vars->env);
	// else if (ft_strcmp(cmds->cmd[0], "export") == 0)
	// 	ft_export();
	// else if (ft_strcmp(cmds->cmd[0], "unset") == 0)
	// 	ft_unset();
	// else if (ft_strcmp(cmds->cmd[0], "exit") == 0)
	// 	ft_exit();
	else
	{
		if (!ft_get_cmd_path(&vars->cmds->cmd[0], vars->env))
		{
			printf("%s: command not found\n", vars->cmds->cmd[0]);
			return ;
		}
		execve(cmds->cmd[0], cmds->cmd, vars->env);
	}
}

void	ft_exec_commands(t_vars *vars)
{
	pid_t	pid;

	ft_open_pipes(vars->cmds);
	ft_open_redirs(vars->cmds);
	while(vars->cmds)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			ft_dup_fds(vars->cmds);
			ft_exec_command(vars, vars->cmds);
		}
		if (vars->cmds->pipe[STDIN_FILENO] != STDIN_FILENO)
			close(vars->cmds->pipe[STDIN_FILENO]);
		if (vars->cmds->pipe[STDOUT_FILENO] != STDOUT_FILENO)
			close(vars->cmds->pipe[STDOUT_FILENO]);
		vars->cmds = vars->cmds->next;
	}
	waitpid(pid, NULL, 0);
}