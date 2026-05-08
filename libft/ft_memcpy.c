/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:39:41 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/11 15:01:43 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*to_dest;
	const unsigned char	*to_src;
	size_t				i;

	if ((!src || !dest) && n > 0)
		return (NULL);
	to_dest = (unsigned char *)dest;
	to_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		to_dest[i] = to_src[i];
		i++;
	}
	return (dest);
}
