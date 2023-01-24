/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:07:39 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 11:32:39 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	ft_w_count(t_lst *tokens)
{
	int		w_count;

	w_count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD
			&& (tokens->prev == NULL
				|| (tokens->prev->type != IN_RED
					&& tokens->prev->type != OUT_RED
					&& tokens->prev->type != IN_REDD
					&& tokens->prev->type != OUT_REDD)))
			w_count++;
		tokens = tokens->next;
	}
	return (w_count);
}

static void	ft_parsing_lists(t_vars *vars, t_lst *tokens,
								t_lst **redir, char **cmd)
{
	if (tokens->type == PIPE || !tokens->next)
	{
		ft_mini_lstadd_back(&vars->cmds, ft_mini_lstnew(cmd, *redir));
		*redir = NULL;
	}
	if (tokens->type == IN_RED || tokens->type == OUT_RED
		|| tokens->type == IN_REDD || tokens->type == OUT_REDD)
		ft_lst_lstadd_back(redir,
			ft_lst_lstnew(ft_strdup(tokens->next->content), tokens->type));
}

t_mini	*ft_parsing(t_vars *vars, t_lst *tokens)
{
	t_lst	*redir;
	char	**cmd;
	int		i;

	vars->cmds = NULL;
	redir = NULL;
	i = 0;
	while (tokens)
	{
		if (i == 0)
			cmd = ft_calloc(ft_w_count(tokens) + 1, sizeof(char *));
		if (tokens->type == WORD && (tokens->prev == NULL
				|| (tokens->prev->type != IN_RED
					&& tokens->prev->type != OUT_RED
					&& tokens->prev->type != IN_REDD
					&& tokens->prev->type != OUT_REDD)))
			cmd[i++] = ft_strdup(tokens->content);
		ft_parsing_lists(vars, tokens, &redir, cmd);
		if (tokens->type == PIPE && tokens->next)
			i = 0;
		tokens = tokens->next;
	}
	return (vars->cmds);
}
