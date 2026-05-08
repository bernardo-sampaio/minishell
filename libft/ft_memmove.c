/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:32:46 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/12 13:52:07 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*to_dest;
	const unsigned char	*to_src;
	size_t				i;

	if ((!src || !dest) && n > 0)
		return (NULL);
	to_dest = (unsigned char *)dest;
	to_src = (const unsigned char *)src;
	if (to_dest > to_src)
	{
		while (n > 0)
		{
			n--;
			to_dest[n] = to_src[n];
		}
	}
	i = 0;
	while (i < n)
	{
		to_dest[i] = to_src[i];
		i++;
	}
	return (dest);
}
