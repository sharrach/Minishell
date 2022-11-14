/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:56:56 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/14 14:55:56 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static  int     ft_isnum(char *str)
// {
//     int i;
    
//     i = 0;
//     while(str[i] && (str[i] == '-' || str[i] == '+'))
//         i++;
//     while(str[i])
//     {
//         if((str[i] <= '0' || str[i] >= '9'))
//             return (0);
//         i++;
//     }
//     return(1);
// }

// void    ft_exit(char **args)
// {
//     int exit;
    
//     exit = NULL;
//     exit = 0;
//     printf("exit\n");
//     if(ft_arrlen(args) == 1)
//         exit = 0;
//     else if(ft_arrlen(args) == 2)
//     {
//         if(ft_isnum(args[1]))
//             exit = ft_atoi(args[1]);
//         else
//         {
//             printf("minishell: exit: %s: numeric argument required", args[2]);
//             exit = 2;
//         }
//     }
//     else if(ft_arrlen(args) > 2)
//     {
//         if(ft_isnum(args[1]))
//         {
//             printf("minishell: %s: too many arguments", args[0]);
//             exit = ft_atoi(args[1]);
//         }
//         else
//         {
//             printf("minishell: exit: %s: numeric argument required", args[2]);
//             exit = 2;
//         }
//     }
// }