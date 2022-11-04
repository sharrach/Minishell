/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:07:39 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/03 13:11:30 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mini	*ft_parsing(t_lst *tokens)
{
	t_mini	*cmds;
	t_lst	*redir;
	char	**cmd;
	int		w_count;
	int 	i;
	t_lst	*tmp;

	cmds = NULL;
	redir = NULL;
	w_count = 0;
	i = 0;
	tmp = tokens;
	while(tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && (tmp->prev == NULL
			|| (tmp->prev->type != IN_RED && tmp->prev->type != OUT_RED
				&& tmp->prev->type != IN_REDD && tmp->prev->type != OUT_REDD)))
			w_count++;
		tmp = tmp->next;
	}
	cmd = (char **)ft_calloc(w_count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == WORD && (tokens->prev == NULL
			|| (tokens->prev->type != IN_RED && tokens->prev->type != OUT_RED
				&& tokens->prev->type != IN_REDD && tokens->prev->type != OUT_REDD)))
			cmd[i++] = tokens->content;
		if (tokens->type == PIPE || !tokens->next)
		{
			ft_mini_lstadd_back(&cmds, ft_mini_lstnew(cmd, redir));
			redir = NULL;
		}
		if (tokens->type == IN_RED || tokens->type == OUT_RED
			|| tokens->type == IN_REDD || tokens->type == OUT_REDD)
		{
			ft_lst_lstadd_back(&redir, ft_lst_lstnew(tokens->next->content, tokens->type));
		}
		if (tokens->type == PIPE && tokens->next)
		{
			w_count = 0;
			i = 0;
			tmp = tokens;
			while(tmp && tmp->type != PIPE)
			{
				if (tmp->type == WORD && (tmp->prev == NULL
					|| (tmp->prev->type != IN_RED && tmp->prev->type != OUT_RED
						&& tmp->prev->type != IN_REDD && tmp->prev->type != OUT_REDD)))
					w_count++;
				tmp = tmp->next;
			}
			cmd = (char **)ft_calloc(w_count + 1, sizeof(char *));
			if (!cmd)
				return (NULL);
		}
		tokens = tokens->next;
	}
	return (cmds);
}
