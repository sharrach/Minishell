/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:34:22 by sharrach          #+#    #+#             */
/*   Updated: 2022/10/18 13:36:18 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_2d(char **arr)
{
    int i;
     
    i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i ++;
    }
    free(arr);
}