/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:18:19 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/03 12:05:42 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*ft_new_token(char *token, t_token_type type)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->token = ft_strdup(token);
	if (!new->token)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->heredoc_fd = -1;
	new->next = NULL;
	return (new);
}

t_tokens	*ft_get_tokens(char *line)
{
	t_tokens	*list;
	size_t		i;
	size_t		next_i;

	list = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
		{
			next_i = ft_tokenize_step(line, i, &list);
			if (!next_i)
			{
				ft_free_tokens(&list);
				return (NULL);
			}
			i = next_i;
		}
	}
	return (list);
}

void	ft_free_tokens(t_tokens **list)
{
	t_tokens	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->heredoc_fd > 2)
			close((*list)->heredoc_fd);
		free((*list)->token);
		free(*list);
		*list = tmp;
	}
}

int	ft_handle_words(char *line, size_t i, t_tokens **list)
{
	t_tokens	*new;
	char		quote;
	char		*word;
	size_t		start;

	new = NULL;
	word = NULL;
	start = i;
	while (line[i] && line[i] != ' ' && !ft_is_operator(line[i]))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
		}
		i++;
	}
	word = ft_substr(line, start, i - start);
	new = ft_new_token(word, WORD);
	free(word);
	if (new)
		ft_lstadd_back(list, new);
	return (i);
}

size_t	ft_tokenize_step(char *line, size_t i, t_tokens **list)
{
	if (ft_is_operator(line[i]))
		return (ft_handle_operators(line, i, list));
	return (ft_handle_words(line, i, list));
}
