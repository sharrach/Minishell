/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:01:52 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 09:51:38 by sharrach         ###   ########.fr       */
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
# include <sys/wait.h>
// # include <linux/limits.h>
# include <limits.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

int	g_exit;
#define BUFFER_SIZE 1

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

typedef struct	s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_vars
{
	t_mini	*cmds;
	t_env	*env;
	char	*input;
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

// freeing and array
// void    free_2d(char **arr);
// // count the lenght of an array
// size_t	ft_arrlen(char **arr);
// // comparing two strings
// int		ft_strcmp(const char *s1, const char *s2);
// char	*ft_strcat(char *dest, const char *src);
// char	*ft_stradd(char const *s1, char const *s2);
// void	ft_strcpy(char *dst, const char *src);


/// execution
void	ft_open_pipes(t_mini *cmds);
void	ft_close_pipes(t_mini *cmds);
void	ft_open_redirs(t_mini *cmds, t_env *env);

//add path
int 	ft_get_cmd_path(char **cmd, t_env *env);

//minishell
t_mini	*ft_parsing(t_lst *tokens);
int		ft_token_type(char *content);
int		syntax_error(t_lst	*tokens);
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
void	ft_env(t_env *env);
int		ft_echo(char **arg);
int		ft_cd(char **args, t_env **env);
void	ft_unset(char **args, t_env **env);
void    ft_export(char **args, t_env **env);
void    ft_exit(char **args);

void	ft_setenv(t_env **env, char *var, char *content);
char	*ft_getenv(t_env *env, char *var);
size_t	ft_varlen(char *str);
void	ft_expand(char **cmd, t_env *env);

int		ft_here_doc(char *del, t_env *env);
void	ft_expand_str(char **str, t_env *env);

#endif

// cat > hh >> hhh > hdf | echo hh

// t_mini	*cmds:
	// cmds[0]:
		// char **cmd:
			// cat
		// t_lst *redir:
			// type: >
			// content: hh

			// type: >>
			// content: hhh

			// type: >
			// content: hdf