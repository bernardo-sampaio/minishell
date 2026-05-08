/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:55:13 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/15 11:55:17 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	int		last;

	if (!str)
		return (NULL);
	s = (char *)str;
	last = 0;
	while (s[last] != '\0')
		last++;
	while (last >= 0)
	{
		if (s[last] == (unsigned char)c)
		{
			return (&s[last]);
		}
		last--;
	}
	return (NULL);
}
