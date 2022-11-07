/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:01:52 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/06 14:02:54 by sharrach         ###   ########.fr       */
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
# include <error.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef	struct s_lst
{
	char			*content;
	int				type;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef	struct  s_mini
{
	char			**cmd;
	int				pipe[2];
	t_lst			*redir;
	struct s_mini	*next;
	struct s_mini	*prev;
}	t_mini;

typedef struct s_vars
{
	t_mini	*cmds;
	char	**env;
	char	**arg;
	char	*input;
}	t_vars;

//linked list minishell
void	ft_mini_lstclear(t_mini **lst);
t_mini	*ft_mini_lstnew(char **cmd, t_lst *redir);
void	ft_mini_lstadd_back(t_mini **lst, t_mini *new);
t_mini	*ft_mini_lstlast(t_mini *lst);

//linked list redir
t_lst	*ft_lst_lstlast(t_lst *lst);
void	ft_lst_lstadd_back(t_lst **lst, t_lst *new);
t_lst	*ft_lst_lstnew(char *name, int type);
void	ft_lst_lstclear(t_lst **lst);

//using function
void    free_2d(char **arr);
size_t	ft_arrlen(char **arr);
int ft_strcmp(const char *s1, const char *s2);


/// execution
void	ft_open_pipes(t_mini *cmds);
void	ft_close_pipes(t_mini *cmds);
void	ft_open_redirs(t_mini *cmds);

//add path
int 	ft_get_cmd_path(char **cmd, char *env[]);

//minishell
t_mini	*ft_parsing(t_lst *tokens);
int		ft_token_type(char *content);
int		syntax_error(t_lst	*tokens);
t_lst	*ft_tokenization(char *input);
void	ft_exec_commands(t_vars *vars);
void	ft_duplicate_env(t_vars *vars, char **env);

//built-ins
int		ft_pwd(void);
void	ft_duplicate_env(t_vars *vars, char **env);
void	ft_env(char **env);
int		ft_echo(char **arg);
int		ft_cd(char	**args, char **env);



char    *ft_getenv(char **env, char *var);
#endif