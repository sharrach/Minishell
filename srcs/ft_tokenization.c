/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:09:14 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/20 14:56:42 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error(t_lst	*tokens)
{
	if (tokens->type == PIPE)
		return (1);
	while (tokens)
	{
		if (tokens->type != WORD
			&& (!tokens->next || (tokens->next && tokens->next->type != WORD)))
			return (1);
		if (tokens->type == QUOTE || tokens->type == DB_QUOTE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	ft_token_type(char *content)
{
	int	type;

	if (!ft_strcmp(content, "|"))
		type = PIPE;
	else if (!ft_strcmp(content, "<"))
		type = IN_RED;
	else if (!ft_strcmp(content, ">"))
		type = OUT_RED;
	else if (!ft_strcmp(content, "<<"))
		type = IN_REDD;
	else if (!ft_strcmp(content, ">>"))
		type = OUT_REDD;
	else if (!ft_strcmp(content, "\""))
		type = DB_QUOTE;
	else if (!ft_strcmp(content, "'"))
		type = QUOTE;
	else
		type = WORD;
	return (type);
}

static	void	quote_redir_handle(char **input, int *i, int *size)
{
	if (((*input)[*i + *size] == '>' && (*input)[*i + *size + 1] == '>')
			|| ((*input)[*i + *size] == '<' && (*input)[*i + *size + 1] == '<'))
		*size += 2;
	else if (ft_strchr("|<>", (*input)[*i + *size]))
		(*size)++;
	else
	{
		while ((*input)[*i + *size] && !ft_strchr("| <>", (*input)[*i + *size]))
		{
			if (((*input)[*i + *size] == '"' || (*input)[*i + *size] == '\'')
				&& (*input)[*i + *size + 1]
					&& ft_strchr(&(*input)[*i + *size + 1], (*input)[*i + *size]))
				*size = ft_strlen((*input)) - ft_strlen(ft_strchr(&(*input)[*i + *size + 1], (*input)[*i + *size]));
			else if ((*input)[*i + *size] == '"' || (*input)[*i + *size] == '\'')
				break ;
			(*size)++;
		}
	}
}

t_lst	*ft_tokenization(char *input)
{
	t_lst	*tokens;
	char	*content;
	int		type;
	int		i;
	int		size;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			i++;
			continue ;
		}
		size = 0;
		quote_redir_handle(&input, &i, &size);
		if (size == 0 && input[i] == input[i + size])
			size = 1;
		content = ft_substr(input, i, size);
		type = ft_token_type(content);
		ft_lst_lstadd_back(&tokens, ft_lst_lstnew(content, type));
		i += size;
	}
	return (tokens);
}
