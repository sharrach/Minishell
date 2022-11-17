/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:52:29 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/17 18:33:46 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_here_doc(char *del, t_env *env)
{
	int		p[2];
	char	*line;

	if (pipe(p) == -1)
		return (perror("pipe"), STDIN_FILENO);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		ft_expand_str(&line, env);
		if (ft_strncmp(line, del, ft_strlen(del)) == 0
			&& line[ft_strlen(del)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, p[STDOUT_FILENO]);
		free(line);
	}
	close(p[STDOUT_FILENO]);
	return (p[STDIN_FILENO]);
}
