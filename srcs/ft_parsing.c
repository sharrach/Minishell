/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:07:39 by sharrach          #+#    #+#             */
/*   Updated: 2022/12/15 16:32:56 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	ft_w_count(t_lst **tmp)
{
	int		w_count;
	t_lst 	*tmp2;

	tmp2 = *tmp;
	w_count = 0;
	while (tmp2 && tmp2->type != PIPE)
	{
		if (tmp2->type == WORD
			&& (tmp2->prev == NULL
				|| (tmp2->prev->type != IN_RED
					&& tmp2->prev->type != OUT_RED
					&& tmp2->prev->type != IN_REDD
					&& tmp2->prev->type != OUT_REDD)))
			w_count++;
		tmp2 = tmp2->next;
	}
	return (w_count);
}

t_mini	*ft_parsing(t_lst *tokens)
{
	t_mini	*cmds;
	t_lst	*redir;
	char	**cmd;
	int		w_count;
	int		i;
	t_lst	*tmp;

	cmds = NULL;
	redir = NULL;
	i = 0;
	tmp = tokens;
	w_count = ft_w_count(&tmp);
	cmd = (char **)ft_calloc(w_count + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == WORD && (tokens->prev == NULL
				|| (tokens->prev->type != IN_RED
					&& tokens->prev->type != OUT_RED
					&& tokens->prev->type != IN_REDD
					&& tokens->prev->type != OUT_REDD)))
			cmd[i++] = tokens->content;
		if (tokens->type == PIPE || !tokens->next)
		{
			ft_mini_lstadd_back(&cmds, ft_mini_lstnew(cmd, redir));
			redir = NULL;
		}
		if (tokens->type == IN_RED || tokens->type == OUT_RED
			|| tokens->type == IN_REDD || tokens->type == OUT_REDD)
			ft_lst_lstadd_back(&redir, ft_lst_lstnew(tokens->next->content, tokens->type));
		if (tokens->type == PIPE && tokens->next)
		{
			i = 0;
			tmp = tokens->next;
			w_count = ft_w_count(&tmp);
			cmd = (char **)ft_calloc(w_count + 1, sizeof(char *));
			if (!cmd)
				return (NULL);
		}
		tokens = tokens->next;
	}
	return (cmds);
}
