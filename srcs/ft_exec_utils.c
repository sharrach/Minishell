/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:59:36 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/23 12:30:55 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtins(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "pwd") == 0
		|| ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

int	ft_builtin_check(t_vars *vars, t_mini *cmds)
{
	if (ft_strcmp(cmds->cmd[0], "env") == 0)
		return (gvar.exit = ft_env(vars->env), 1);
	else if (ft_strcmp(cmds->cmd[0], "echo") == 0)
		return (gvar.exit = ft_echo(cmds->cmd), 1);
	else if (ft_strcmp(cmds->cmd[0], "pwd") == 0)
		return (gvar.exit = ft_pwd(), 1);
	else if (ft_strcmp(cmds->cmd[0], "cd") == 0)
		return (gvar.exit = ft_cd(cmds->cmd, &vars->env), 1);
	else if (ft_strcmp(cmds->cmd[0], "unset") == 0)
		return (gvar.exit = ft_unset(cmds->cmd, &vars->env), 1);
	else if (ft_strcmp(cmds->cmd[0], "export") == 0)
		return (gvar.exit = ft_export(cmds->cmd, &vars->env), 1);
	else if (ft_strcmp(cmds->cmd[0], "exit") == 0)
		return (gvar.exit = ft_exit(cmds->cmd), 1);
	return (0);
}

void	ft_dup_fds(t_mini *cmds)
{
	if (cmds->red[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(cmds->red[STDIN_FILENO], STDIN_FILENO);
		close(cmds->red[STDIN_FILENO]);
	}
	else if (cmds->pipe[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(cmds->pipe[STDIN_FILENO], STDIN_FILENO);
		close(cmds->pipe[STDIN_FILENO]);
		if (cmds->prev && cmds->prev->pipe[STDOUT_FILENO] != STDOUT_FILENO)
			close(cmds->prev->pipe[STDOUT_FILENO]);
	}
	if (cmds->red[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(cmds->red[STDOUT_FILENO], STDOUT_FILENO);
		close(cmds->red[STDOUT_FILENO]);
	}
	else if (cmds->pipe[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(cmds->pipe[STDOUT_FILENO], STDOUT_FILENO);
		close(cmds->pipe[STDOUT_FILENO]);
		if (cmds->next && cmds->next->pipe[STDIN_FILENO] != STDIN_FILENO)
			close(cmds->next->pipe[STDIN_FILENO]);
	}
}

void	ft_dup_close(int *std)
{
	dup2(std[STDOUT_FILENO], STDOUT_FILENO);
	close(std[STDOUT_FILENO]);
	dup2(std[STDIN_FILENO], STDIN_FILENO);
	close(std[STDIN_FILENO]);
}

void	ft_perr(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
}
