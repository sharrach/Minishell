/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:21:03 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/16 20:07:20 by sharrach         ###   ########.fr       */
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
	if (execve(cmd[0], cmd, envp) == -1)
	{
		perror("minishell: execve");
		exit(EXIT_FAILURE);
	}
}

void	ft_perr(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
}

static int builtin_check(t_vars *vars, t_mini *cmds)
{
	if (ft_strcmp(cmds->cmd[0], "env") == 0)
		return (gvar.exit = ft_env(vars->env), 0);
	else if (ft_strcmp(cmds->cmd[0], "echo") == 0)
		return (gvar.exit = ft_echo(cmds->cmd), 0);
	else if (ft_strcmp(cmds->cmd[0], "pwd") == 0)
		return (gvar.exit = ft_pwd(), 0);
	else if (ft_strcmp(cmds->cmd[0], "cd") == 0)
		return (gvar.exit = ft_cd(cmds->cmd, &vars->env), 0);
	else if (ft_strcmp(cmds->cmd[0], "unset") == 0)
		return (gvar.exit = ft_unset(cmds->cmd, &vars->env), 0);
	else if (ft_strcmp(cmds->cmd[0], "export") == 0)
		return (gvar.exit = ft_export(cmds->cmd, &vars->env), 0);
	else if (ft_strcmp(cmds->cmd[0], "exit") == 0)
		return (gvar.exit = ft_exit(cmds->cmd), 0);
	return (1);
}

void	ft_exec_command(t_vars *vars, t_mini *cmds, int is_fork)
{
	if (builtin_check(vars, cmds) == 1)
	{
		if (access(cmds->cmd[0], F_OK) == 0)
		{
			if (access(cmds->cmd[0], X_OK) != 0)
			{
				ft_perr(cmds->cmd[0], "Permission denied");
				exit(126);
			}
		}
		else
			ft_get_cmd_path(&cmds->cmd[0], vars->env);
		ft_execve(cmds->cmd, vars->env);	
	}
	if (is_fork)
		exit(gvar.exit);
}

static void ft_sig_status(pid_t pid, t_vars *vars)
{	
	int status;
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	gvar.exit = WEXITSTATUS(status);
	if (WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		gvar.exit = 130;
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putendl_fd("Quit", STDOUT_FILENO);
		gvar.exit = 131;
	}
	sigaction(SIGINT, &vars->act, NULL);
}

static void ft_exec_cmnd(t_mini *cmds, t_vars *vars, int is_fork, pid_t *pid)
{
	while (cmds)
	{
		ft_expand(cmds->cmd, vars->env);
		ft_remove_quotes(cmds->cmd);
		if (is_fork)
		{
			signal(SIGINT, SIG_IGN);
			*pid = fork();
		}
		if (*pid == -1)
			perror("fork");
		if (*pid == 0)
		{
			if (is_fork)
			{
				signal(SIGINT, NULL);
				signal(SIGQUIT, NULL);
			}
			ft_dup_fds(cmds);
			ft_close_all_fds(vars->cmds);
			ft_exec_command(vars, cmds, is_fork);
		}
		ft_close_fds(&cmds);
		cmds = cmds->next;
	}
}
static void ft_dup_close(int *std)
{
	dup2(std[STDOUT_FILENO], STDOUT_FILENO);
	close(std[STDOUT_FILENO]);
	dup2(std[STDIN_FILENO], STDIN_FILENO);
	close(std[STDIN_FILENO]);

}
void	ft_exec_commands(t_vars *vars)
{
	t_mini	*cmds;
	int		is_fork;
	int		std[2];
	pid_t	pid;

	is_fork = 1;
	pid = 0;
	ft_open_pipes(vars->cmds);
	if (!ft_open_redirs(vars->cmds, vars->env))
		return ;
	if (ft_mini_lstsize(vars->cmds) == 1 && ft_builtins(vars->cmds->cmd[0]))
		is_fork = 0;
	if (!is_fork)
	{
		std[STDIN_FILENO] = dup(STDIN_FILENO);
		std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	}
	cmds = vars->cmds;
	ft_exec_cmnd(cmds, vars, is_fork, &pid);
	if (is_fork)
		ft_sig_status(pid, vars);
	if (!is_fork)
		ft_dup_close(std);
}
