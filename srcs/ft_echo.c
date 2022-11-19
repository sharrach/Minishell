/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:23:24 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 15:10:04 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_echo(char **arg)
{
    int i;
    int j;
    int    nl;
    
    i = 1;
    j = 1;
    nl = 1;
    while (arg[i] && arg[i][0] == '-')
    {
        j = 1;
        while (arg[i][j] && arg[i][j] == 'n')
            j++;
        if (!arg[i][j]) {
            nl = 0;
            i++;
        }
        else
            break ;
    }
    while (arg[i])
    {
        printf("%s", arg[i]);
        if (arg[i + 1])
            printf(" ");
        i ++;
    }
    if (nl)
        printf("\n");
    return (0);
}
