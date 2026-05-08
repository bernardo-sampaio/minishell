/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:24:04 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/15 13:24:08 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*sb;
	size_t	i;
	size_t	j;

	if (!big || !little)
		return (NULL);
	sb = (char *)big;
	i = 0;
	if (little[i] == '\0')
		return (sb);
	while (i < len && sb[i] != '\0')
	{
		j = 0;
		while ((i + j) < len && sb[i + j] != '\0' && sb[i + j] == little[j])
		{
			if (little[j + 1] == '\0')
				return (&sb[i]);
			++j;
		}
		++i;
	}
	return (NULL);
}
