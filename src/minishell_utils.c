/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:22:16 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/03 13:13:58 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_args(t_tokens *token)
{
	t_tokens	*tmp;
	int			i;

	tmp = token;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		else if (tmp->type >= RED_IN && tmp->type <= APPEND)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_take_args(t_tokens *token)
{
	t_tokens	*tmp;
	char		**args;
	int			i;

	args = malloc(sizeof(char *) * (ft_count_args(token) + 1));
	if (!args)
		return (NULL);
	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type >= RED_IN && tmp->type <= APPEND)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		else if (tmp->type == WORD)
			args[i++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}
