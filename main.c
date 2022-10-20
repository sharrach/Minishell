/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:36:50 by sharrach          #+#    #+#             */
/*   Updated: 2022/10/20 16:35:52 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_type(char *content)
{
	int	type;

	if (!strcmp(content, "|"))
		type = PIPE;
	else if (!strcmp(content, "<"))
		type = IN_RED;
	else if (!strcmp(content, ">"))
		type = OUT_RED;
	else if (!strcmp(content, "<<"))
		type = IN_REDD;
	else if (!strcmp(content, ">>"))
		type = OUT_REDD;
	else if (!strcmp(content, "\""))
		type = DB_QUOTE;
	else if (!strcmp(content, "'"))
		type = QUOTE;
	else
		type = WORD;
	return (type);
}

t_lst	*ft_tokenization(char *input)
{
	t_lst	*tokens;
	char	*content;
	int		type;
	int 	i;
	int		start;
	int		quote;

	tokens = NULL;
	i = 0;
	while (input[i] == ' ')
		i++;
	start = i;
	quote = 0;
	while(1)
	{
		if (quote == 0 && (input[i] == '"' || input[i] == '\''))
			quote = input[i];
		else if (quote == input[i])
			quote = 0;
		if (quote == 0 && ft_strchr("|<> \0", input[i]) && i != 0)
		{
			// if ((input[i] == '<' && input[i + 1] == '<') 
			// 	|| (input[i] == '>' && input[i + 1] == '>'))
			// {
			// 	type = ft_token_type(content);
			// 	ft_lst_lstadd_back(&tokens, ft_lst_lstnew(content, type));
			// }
			content = ft_substr(input, start, (i - start));
			type = ft_token_type(content);
			ft_lst_lstadd_back(&tokens, ft_lst_lstnew(content, type));
			while (input[i] == ' ')
				i++;
			start = i;
		}
		if (!input[i])
			break;
		i ++;
	}
	return (tokens);
}

static  void handle_signals(int signo) {
	if (signo == SIGINT) {
		printf("You pressed Ctrl+C\n");
	}
}

int main ()
{
	t_lst *tokens;
	char *input;
	char *shell_prompt = "Tzz-shell> ";

	signal(SIGINT, handle_signals);
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	while (1)
	{
		input = readline(shell_prompt);
		if (!input)
			break;
		add_history(input);
		tokens = ft_tokenization(input);
		if (!tokens)
			break;
		while (tokens != NULL)
		{
			printf("content: '%s'\n", tokens->content);
			printf("type: %d\n\n", tokens->type);
			tokens = tokens->next;
		}
	}
	return 0;
}