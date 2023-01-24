/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:33:24 by sharrach          #+#    #+#             */
/*   Updated: 2021/11/03 15:33:27 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		i = 0;
		while (src[i] && i + dst_len < dstsize - 1)
		{
			dst[i + dst_len] = src[i];
			i ++;
		}
		if (i > 0)
			dst[i + dst_len] = '\0';
	}
	if (dstsize >= dst_len)
		return (dst_len + src_len);
	else
		return (src_len + dstsize);
}
