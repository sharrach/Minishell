/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:52:29 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/16 14:55:48 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_heredoc(char *del, t_vars *cmds)
// {
//     pid_t	reader;
//     char	*line;
//     int		fd[2];

// 	if (pipe(fd) == -1)
// 		perror("pipe");
// 	reader = fork();
// 	if (reader == 0)
// 	{
// 		close(fd[0]);
// 		while (get_next_line(&line))
// 		{
// 			if (ft_strncmp(line, del, ft_strlen(del)) == 0)
// 				exit(EXIT_SUCCESS);
// 			printf("%s", line);
// 		}
// 	}
// 	else
// 	{// 		close(fd[1]);

// 		dup2(fd[0], STDIN_FILENO);
// 		wait(NULL);
// 	}
// }

void ft_heredoc(t_mini *cmds, char *dele)
{
	t_lst *redir;
	t_mini *cmd;
	char	*here_doc;
	// int		*heredoc;

	// env = NULL;
	cmd = cmds;
	// printf("here1\n");
	while(cmd)
	{
		// printf("here2\n");
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == IN_REDD)
			{
				// printf("here3\n");
				while(1)
				{
					here_doc = get_next_line(1);
					ft_putendl_fd("> ", STDOUT_FILENO);
					if (!here_doc)
						break;
					if (redir->next)
						dele = redir->next->content;
					// printf("here4\n");
					// printf("here5\n");
					else if (ft_strncmp(here_doc, dele, ft_strlen(dele)) == 0)
					{
						printf("here6\n");
						free(here_doc);
						here_doc = 0;
						break;
					}
					else
					{

						printf("here10\n");
						ft_putendl_fd(here_doc, STDOUT_FILENO);
						free(here_doc);
						here_doc = 0;
					}
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	
	
}