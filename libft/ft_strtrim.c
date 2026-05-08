/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:46:16 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/23 15:55:59 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_i(char const *s1, char const *set)
{
	int	i;
	int	len_set;

	len_set = ft_strlen(set);
	i = 0;
	while (s1[i] != '\0' && ft_memchr(set, s1[i], len_set))
	{
		i++;
	}
	return (i);
}

static int	ft_len_f(char const *s1, char const *set)
{
	int	f;
	int	len_s1;
	int	len_set;

	len_s1 = ft_strlen(s1);
	len_set = ft_strlen(set);
	f = len_s1 - 1;
	while (s1[f] != '\0' && ft_memchr(set, s1[f], len_set))
	{
		f--;
	}
	return (f);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		i;
	int		f;
	int		len_new_str;

	if (!s1 || !set)
		return (NULL);
	i = ft_len_i(s1, set);
	f = ft_len_f(s1, set);
	len_new_str = f - i + 1;
	if (f < i)
		return (ft_strdup(""));
	new_str = malloc(len_new_str + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1 + i, len_new_str + 1);
	return (new_str);
}
