/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:59:57 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/19 09:37:35 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static	char	*ft_str_cpy(char *dst, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s = ((char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s == 0)
		return (NULL);
	ft_str_cpy(s, (char *) s1);
	ft_strcat(s, (char *) s2);
	return (s);
}
