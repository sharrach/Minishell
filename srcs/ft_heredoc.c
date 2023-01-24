/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:52:29 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 17:54:30 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_var_init(char **new_str, int *i, int *len)
{
		*new_str = ft_strdup("");
		*len = 0;
		*i = 0;
}

static void ft_return(char **new_str, int *i, int *len, char **str)
{
	*new_str = ft_stradd2(*new_str, ft_substr((*str), *i - *len, *len));
	free(*str);
	*str = *new_str;
}

static void	ft_expand_heredoc(char **str, t_env *env)
{
	char	*new_str;
	char	*var;
	int		len;
	int		i;

	ft_var_init(&new_str, &i, &len);
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (ft_isalpha((*str)[i + 1])
			|| ft_strchr("_?", (*str)[i + 1])))
		{
			new_str = ft_stradd2(new_str, ft_substr((*str), i - len, len));
			var = ft_substr(*str, i + 1, ft_expand_varlen(&(*str)[i + 1]));
			if (ft_strcmp(var, "?") == 0)
				new_str = ft_stradd2(new_str, ft_itoa(g_var.exit));
			else if (ft_getenv(env, var))
				new_str = ft_stradd(new_str, ft_getenv(env, var));
			free(var);
			len = -1;
			i += ft_expand_varlen(&(*str)[i + 1]);
		}
		len++;
		i++;
	}
	ft_return(&new_str, &i, &len, str);
}

static int	ft_here_doc_loop(char **line, char **del)
{
	ft_putstr_fd("> ", STDOUT_FILENO);
	(*line) = get_next_line(STDIN_FILENO);
	if (!(*line) || (ft_strncmp((*line), *del, ft_strlen(*del)) == 0
		&& (*line)[ft_strlen(*del)] == '\n'))
	{
		free((*line));
		return (0);
	}
	return (1);
}

int	ft_here_doc(char **del, t_env *env)
{
	int		p[2];
	int		is_expand;
	char	*line;

	if (pipe(p) == -1)
		return (perror("pipe"), STDIN_FILENO);
	is_expand = 0;
	if (!ft_strchr(*del, '\'') && !ft_strchr(*del, '"'))
		is_expand = 1;
	ft_remove_quotes_str(del);
	g_var.here_doc = 1;
	while (g_var.here_doc)
	{
		if (!ft_here_doc_loop(&line, del))
			break ;
		if (is_expand)
			ft_expand_heredoc(&line, env);
		ft_putstr_fd(line, p[STDOUT_FILENO]);
		free(line);
	}
	close(p[STDOUT_FILENO]);
	if (!g_var.here_doc)
		return (close(p[STDIN_FILENO]), STDIN_FILENO);
	return (g_var.here_doc = 0, p[STDIN_FILENO]);
}
