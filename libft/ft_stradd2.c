/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:14:28 by sharrach          #+#    #+#             */
/*   Updated: 2022/11/24 17:34:52 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd2(char const *s1, char const *s2)
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
	free((void *)s2);
	return (s);
}
