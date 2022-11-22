/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:11:16 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 16:09:1 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_builtins(char *name)
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

void	ft_dup_fds(t_mini *cmds)
{
	if (cmds->pipe[STDIN_FILENO] != STDIN_FILENO)
	{
		if (cmds->prev->pipe[STDOUT_FILENO] != STDOUT_FILENO)
			close(cmds->prev->pipe[STDOUT_FILENO]);
		dup2(cmds->pipe[STDIN_FILENO], STDIN_FILENO);
		close(cmds->pipe[STDIN_FILENO]);
		cmds->pipe[STDIN_FILENO] = STDIN_FILENO;
	}
	if (cmds->pipe[STDOUT_FILENO] != STDOUT_FILENO)
	{
		if (cmds->next->pipe[STDIN_FILENO] != STDIN_FILENO)
			close(cmds->next->pipe[STDIN_FILENO]);
		dup2(cmds->pipe[STDOUT_FILENO], STDOUT_FILENO);
		close(cmds->pipe[STDOUT_FILENO]);
		cmds->pipe[STDOUT_FILENO] = STDOUT_FILENO;
	}
}

static void	ft_execve(char **cmd, t_env *env)
{
	char	**envp;
	int		i;

	envp = (char **)ft_calloc(ft_env_lstsize(env) + 1, sizeof(char *));
	if (!envp)
		return ;
	i = 0;
	while (env)
	{
		envp[i] = ft_strjoin(env->var, "=");
		envp[i] = ft_stradd(envp[i], env->content);
		i++;
		env = env->next;
	}
	execve(cmd[0], cmd, envp);
}

void	ft_exec_command(t_vars *vars, t_mini *cmds)
{
	if (ft_strcmp(cmds->cmd[0], "env") == 0)
		gvar.exit = ft_env(vars->env);
	else if (ft_strcmp(cmds->cmd[0], "echo") == 0)
		gvar.exit = ft_echo(cmds->cmd);
	else if (ft_strcmp(cmds->cmd[0], "pwd") == 0)
		gvar.exit = ft_pwd();
	else if (ft_strcmp(cmds->cmd[0], "cd") == 0)
		gvar.exit = ft_cd(cmds->cmd, &vars->env);
	else if (ft_strcmp(cmds->cmd[0], "unset") == 0)
		gvar.exit = ft_unset(cmds->cmd, &vars->env);
	else if (ft_strcmp(cmds->cmd[0], "export") == 0)
		gvar.exit = ft_export(cmds->cmd, &vars->env);
	else if (ft_strcmp(cmds->cmd[0], "exit") == 0)
		gvar.exit = ft_exit(cmds->cmd);
	else
	{
		if (!ft_get_cmd_path(&cmds->cmd[0], vars->env))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmds->cmd[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			exit(127);
		}
		ft_execve(cmds->cmd, vars->env);
	}
}

void	ft_exec_commands(t_vars *vars)
{
	t_mini	*cmd;
	int		is_fork;
	pid_t	pid;

	is_fork = 1;
	pid = 0;
	ft_expand(vars->cmds->cmd, vars->env);
	ft_open_pipes(vars->cmds);
	ft_open_redirs(vars->cmds, vars->env);
	if (ft_mini_lstsize(vars->cmds) == 1 && ft_builtins(vars->cmds->cmd[0]))
		is_fork = 0;
	cmd = vars->cmds;
	while (cmd)
	{
		if (is_fork)
			pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			ft_dup_fds(cmd);
			ft_exec_command(vars, cmd);
		}
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
		cmd = cmd->next;
	}
	if (is_fork)
		waitpid(pid, NULL, 0);
}
