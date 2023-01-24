/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:21:03 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 13:17:40 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	ft_sig_status(pid_t pid, t_vars *vars)
{
	int	status;

	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	g_var.exit = WEXITSTATUS(status);
	if (WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_var.exit = 130;
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putendl_fd("Quit", STDOUT_FILENO);
		g_var.exit = 131;
	}
	sigaction(SIGINT, &vars->act, NULL);
}

void	ft_exec_command(t_vars *vars, t_mini *cmds, int is_fork)
{
	struct stat	buf;

	if (!ft_builtin_check(vars, cmds))
	{
		if (access(cmds->cmd[0], F_OK) == 0)
		{
			if (stat(cmds->cmd[0], &buf) == 0 && S_ISDIR(buf.st_mode))
			{
				ft_perr(cmds->cmd[0], "Is a directory");
				exit(126);
			}
			else if (access(cmds->cmd[0], X_OK) == -1)
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
		exit(g_var.exit);
}

static void	ft_exec_cmnd(t_mini *cmds, t_vars *vars, int is_fork, pid_t *pid)
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
