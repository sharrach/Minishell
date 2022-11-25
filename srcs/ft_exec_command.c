/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:21:03 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/25 18:18:11 by iellyass         ###   ########.fr       */
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
		if (cmds->prev && cmds->prev->pipe[STDOUT_FILENO] != STDOUT_FILENO)
			close(cmds->prev->pipe[STDOUT_FILENO]);
		dup2(cmds->pipe[STDIN_FILENO], STDIN_FILENO);
		close(cmds->pipe[STDIN_FILENO]);
		cmds->pipe[STDIN_FILENO] = STDIN_FILENO;
	}
	if (cmds->pipe[STDOUT_FILENO] != STDOUT_FILENO)
	{
		if (cmds->next && cmds->next->pipe[STDIN_FILENO] != STDIN_FILENO)
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
	int		is_fork;
	int		status;
	int		std[2];
	pid_t	pid;

	is_fork = 1;
	pid = 0;
	ft_expand(vars->cmds->cmd, vars->env);
	ft_remove_quote(vars->cmds->cmd);
	ft_open_pipes(vars->cmds);
	ft_open_redirs(vars->cmds, vars->env);
	if (ft_mini_lstsize(vars->cmds) == 1 && ft_builtins(vars->cmds->cmd[0]))
		is_fork = 0;
	if (!is_fork)
	{
		std[STDIN_FILENO] = dup(STDIN_FILENO);
		std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	}
	while (vars->cmds)
	{
		if (is_fork)
		{
			signal(SIGINT, SIG_IGN);
			pid = fork();
		}
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			signal(SIGINT, NULL);
			signal(SIGQUIT, NULL);
			ft_dup_fds(vars->cmds);
			ft_exec_command(vars, vars->cmds);
		}
		ft_close_pipes(vars->cmds);
		vars->cmds = vars->cmds->next;
	}
	if (is_fork)
	{
		waitpid(pid, &status, 0);
		while (waitpid(-1, NULL, 0) != -1)
			;
		gvar.exit = WEXITSTATUS(status);
		if (WTERMSIG(status) == SIGINT)
			gvar.exit = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			gvar.exit = 131;
	}
	if (!is_fork)
	{
		dup2(std[STDOUT_FILENO], STDOUT_FILENO);
		close(std[STDOUT_FILENO]);
		dup2(std[STDIN_FILENO], STDIN_FILENO);
		close(std[STDIN_FILENO]);
	}
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, SIG_IGN);
}
