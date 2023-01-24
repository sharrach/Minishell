/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:01:03 by sharrach          #+#    #+#             */
/*   Updated: 2021/11/12 18:01:05 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_n(long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{	
	char	*str;
	long	nb;
	size_t	nb_len;
	size_t	negative;

	negative = 0;
	if (n < 0)
		negative = 1;
	nb = n;
	if (nb < 0)
		nb = -nb;
	nb_len = ft_n(nb);
	str = malloc(nb_len + negative + 1);
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[nb_len + negative] = '\0';
	while (nb_len)
	{
		str[nb_len + negative - 1] = (nb % 10) + '0';
		nb /= 10;
		nb_len--;
	}
	return (str);
}
