/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:48:48 by bsampaio          #+#    #+#             */
/*   Updated: 2025/06/27 14:48:16 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_counter(const char *s, char c)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_aloc_word(const char *s, char c, size_t *pos)
{
	size_t	start;
	size_t	tam;
	char	*word;

	if (!s)
		return (NULL);
	while (s[*pos] && s[*pos] == c)
		(*pos)++;
	start = *pos;
	tam = 0;
	while (s[*pos] && s[*pos] != c)
	{
		(*pos)++;
		tam++;
	}
	word = malloc(tam + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + start, tam + 1);
	return (word);
}

static char	**ft_free(char **words, size_t i)
{
	while (i-- > 0)
		free(words[i]);
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;
	size_t	pos;
	size_t	n_word;

	if (!s)
		return (NULL);
	n_word = ft_counter(s, c);
	words = malloc(sizeof(char *) * (n_word + 1));
	if (!words)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < n_word)
	{
		words[i] = ft_aloc_word(s, c, &pos);
		if (!words[i])
			return (ft_free(words, i));
		i++;
	}
	words[n_word] = NULL;
	return (words);
}
