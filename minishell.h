/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:01:52 by sharrach          #+#    #+#             */
/*   Updated: 2022/10/18 12:56:57 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <error.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef	struct s_redir
{
	char			*name;
	int				type;
	struct s_redir	*next;
}	t_redir;

typedef	struct  s_mini
{
	char			**cmd;
	int				pipe[2];
	t_redir			redir;
	struct s_mini	*next;
}	t_mini;

#endif