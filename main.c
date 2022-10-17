/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:36:50 by sharrach          #+#    #+#             */
/*   Updated: 2022/10/17 10:35:22 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  void handle_signals(int signo) {
  if (signo == SIGINT) {
    printf("You pressed Ctrl+C\n");
  }
}

int main (int argc, char **argv)
{
  char *input;
  char *shell_prompt = "Tzz-shell> ";
  if (signal(SIGINT, handle_signals) == SIG_ERR) {
    printf("failed to register interrupts with kernel\n");
  }

  while (1) 
  {
    input = readline(shell_prompt);
    if (!input)
      break;
  }  
  return 0;
}