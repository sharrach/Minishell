/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:52:29 by sharrach          #+#    #+#             */
/*   Updated: 2022/12/15 18:39:09 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_here_doc(char *del, t_env *env)
{
	int		p[2];
	int		is_expand;
	char	*line;

	if (pipe(p) == -1)
		return (perror("pipe"), STDIN_FILENO);
	ft_expand_str(&del, env);
	is_expand = 0;
	if (!ft_strchr(del, '\'') && !ft_strchr(del, '"'))
		is_expand = 1;
	ft_remove_quotes_str(&del);
	gvar.here_doc = 1;
	while (gvar.here_doc)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, del, ft_strlen(del)) == 0
			&& line[ft_strlen(del)] == '\n'))
		{
			free(line);
			break ;
		}
		if (is_expand)
			ft_expand_str(&line, env);
		ft_putstr_fd(line, p[STDOUT_FILENO]);
		free(line);
	}
	close(p[STDOUT_FILENO]);
	if (!gvar.here_doc)
		return (close(p[STDIN_FILENO]), STDIN_FILENO);
	return (p[STDIN_FILENO]);
}
