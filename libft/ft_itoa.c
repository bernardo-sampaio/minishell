/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:50:43 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/24 13:51:03 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		digits;
	int		is_neg;
	char	*str;
	long	nbr;

	nbr = n;
	is_neg = (nbr < 0);
	if (is_neg)
		nbr = -nbr;
	digits = count_digits(nbr) + is_neg;
	str = malloc(digits + 1);
	if (!str)
		return (NULL);
	str[digits] = '\0';
	while (digits-- > is_neg)
	{
		str[digits] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}
