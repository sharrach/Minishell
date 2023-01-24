/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:01:52 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 16:29:29 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
// # include <error.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

# define BUFFER_SIZE 1

enum e_tokens {
	PIPE,
	IN_RED,
	IN_REDD,
	OUT_RED,
	OUT_REDD,
	QUOTE,
	DB_QUOTE,
	WORD
};

typedef struct s_gvar
{
	int	exit;
	int	here_doc;
}	t_gvar;

extern t_gvar	g_var;

typedef struct s_lst
{
	char			*content;
	int				type;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef struct s_mini
{
	char			**cmd;
	int				pipe[2];
	int				red[2];
	t_lst			*redir;
	struct s_mini	*next;
	struct s_mini	*prev;
}	t_mini;

typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_vars
{
	t_mini				*cmds;
	t_env				*env;
	char				*input;
	struct sigaction	act;
}	t_vars;

//linked list minishell
int		ft_mini_lstsize(t_mini *lst);
void	ft_mini_lstclear(t_mini **lst);
t_mini	*ft_mini_lstnew(char **cmd, t_lst *redir);
void	ft_mini_lstadd_back(t_mini **lst, t_mini *new);
t_mini	*ft_mini_lstlast(t_mini *lst);

//linked list redir
t_lst	*ft_lst_lstlast(t_lst *lst);
void	ft_lst_lstadd_back(t_lst **lst, t_lst *new);
t_lst	*ft_lst_lstnew(char *name, int type);
void	ft_lst_lstclear(t_lst **lst);

// linkend list env
int		ft_env_lstsize(t_env *lst);
t_env	*ft_env_lstlast(t_env *env);
void	ft_env_lstadd_back(t_env **env, t_env *new);
t_env	*ft_env_lstnew(char *var, char *content);
void	ft_env_lstclear(t_env **env);

/// execution
void	ft_open_pipes(t_mini *cmds);
void	ft_close_fds(t_mini **cmd);
int		ft_open_redirs(t_mini *cmds, t_env *env);
void	ft_close_all_fds(t_mini *cmds);
/// execution utils
void	ft_perr(char *cmd, char *error);
int		ft_builtins(char *name);
void	ft_dup_fds(t_mini *cmds);
void	ft_dup_close(int *std);
int		ft_builtin_check(t_vars *vars, t_mini *cmds);

//add path
int		ft_get_cmd_path(char **cmd, t_env *env);

//minishell
t_mini	*ft_parsing(t_vars *vars, t_lst *tokens);
int		ft_token_type(char *content);
int		ft_syntax_error(t_lst	*tokens);
t_lst	*ft_tokenization(char *input);
void	ft_exec_commands(t_vars *vars);
void	ft_duplicate_env(t_vars *vars, char **env);
t_env	*ft_duplicate_export(t_env *env);

//get next line
char	*get_next_line(int fd);
char	*ft_strnljoin(char *s1, char *s2);
void	ft_strcpy(char *dst, const char *src);

//built-ins
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_echo(char **arg);
int		ft_cd(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);
void	ft_unset_var(char *arg, t_env **env);
int		ft_export(char **args, t_env **env);
int		ft_exit(char **args);
//built-ins utils
void	ft_swap(t_env **env);
void	check_content(t_env	*holder);

void	ft_setenv(t_env **env, char *var, char *content);
char	*ft_getenv(t_env *env, char *var);
size_t	ft_varlen(char *str);
void	ft_expand(char **cmd, t_env *env);

int		ft_here_doc(char **del, t_env *env);
void	ft_expand_str(char **str, t_env *env, int quote, int len);

int		ft_open_heredoc(t_mini **cmds, t_env *env, t_lst **redir);
//signals
void	ft_handle_signals(int signo);

//quotes
void	ft_remove_quotes(char **cmd);
void	ft_remove_quotes_str(char **str);

//utils
void	ft_perr(char *cmd, char *error);
int		ft_expand_varlen(char *str);

void	ft_shlvl_increment(t_env *env);
int		ft_alphanum_check(char *str);

#endif