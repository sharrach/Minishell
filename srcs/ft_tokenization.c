/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:09:14 by sharrach          #+#    #+#             */
/*   Updated: 2023/01/24 18:10:29 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_syntax_error(t_lst *tokens)
{
	if (tokens->type == PIPE)
		return (1);
	while (tokens)
	{
		if (tokens->type == PIPE
			&& (tokens->next && ((tokens->next->type == IN_RED)
					|| (tokens->next->type == IN_REDD)
					|| (tokens->next->type == OUT_RED)
					|| (tokens->next->type == OUT_REDD))))
		{
			tokens = tokens->next;
			continue ;
		}
		if (tokens->type != WORD
			&& (!tokens->next
				|| (tokens->next && (tokens->next->type != WORD))))
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

static void	ft_get_token_size(char **input, int i, int *size)
{
	char	*str;

	if (((*input)[i + *size] == '>' && (*input)[i + *size + 1] == '>')
		|| ((*input)[i + *size] == '<' && (*input)[i + *size + 1] == '<'))
		*size += 2;
	else if (ft_strchr("|<>", (*input)[i + *size]))
		(*size)++;
	else
	{
		while ((*input)[i + *size] && !ft_strchr("| <>", (*input)[i + *size]))
		{
			str = ft_strchr(&(*input)[i + *size + 1], (*input)[i + *size]);
			if (((*input)[i + *size] == '"' || (*input)[i + *size] == '\'')
				&& (*input)[i + *size + 1] && str)
				*size = ft_strlen(&(*input)[i]) - ft_strlen(str);
			else if ((*input)[i + *size] == '"' || (*input)[i + *size] == '\'')
				break ;
			(*size)++;
		}
	}
	if (*size == 0 && input[i] == input[i + *size])
		*size = 1;
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
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		size = 0;
		ft_get_token_size(&input, i, &size);
		content = ft_substr(input, i, size);
		type = ft_token_type(content);
		ft_lst_lstadd_back(&tokens, ft_lst_lstnew(content, type));
		i += size;
	}
	return (tokens);
}
