/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:34:22 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/09 16:12:42 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i ++;
    return (s1[i] - s2[i]);
}

size_t	ft_arrlen(char **arr)
{
	size_t	arrlen;

	arrlen = 0;
	while (arr[arrlen])
		arrlen ++;
	return (arrlen);
}

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

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;
	int	lendest;
	int	lensrc;
	int	lenofboth;

	i = 0;
	j = 0;
	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	lenofboth = lendest + lensrc;
	while (i < lendest)
		i++;
	while (i < lenofboth)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_strcpy(char *dst, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_stradd(char const *s1, char const *s2)
{
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s = ((char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s == 0)
		return (NULL);
	ft_strcpy(s, (char *) s1);
	ft_strcat(s, (char *) s2);
	free((void *)s1);
	return (s);
}
