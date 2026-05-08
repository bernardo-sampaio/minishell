/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:27:37 by bsampaio          #+#    #+#             */
/*   Updated: 2026/04/20 15:10:35 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_redir(t_tokens *curr)
{
	if (!curr->next || curr->next->type != WORD)
	{
		if (curr->next)
			return (ft_syntax_error(curr->next->token));
		return (ft_syntax_error("newline"));
	}
	return (1);
}

int	ft_check_parenthesis(t_tokens *curr, int *open_p)
{
	if (curr->type == OPEN_PARENT)
	{
		(*open_p)++;
		if (!curr->next)
			return (ft_syntax_error("newline"));
		if ((curr->next->type >= AND && curr->next->type <= BACKGROUND)
			|| curr->next->type == CLOSE_PARENT)
			return (ft_syntax_error(curr->next->token));
	}
	else if (curr->type == CLOSE_PARENT)
	{
		(*open_p)--;
		if (*open_p < 0)
			return (ft_syntax_error(curr->token));
		if (curr->next && (curr->next->type == WORD
				|| curr->next->type == OPEN_PARENT))
			return (ft_syntax_error(curr->next->token));
	}
	return (1);
}

int	ft_check_operators(t_tokens *curr)
{
	if (!curr->next)
		return (ft_syntax_error(curr->token));
	if ((curr->next->type >= AND && curr->next->type <= BACKGROUND)
		|| (curr->next->type >= OPEN_PARENT
			&& curr->next->type <= CLOSE_PARENT))
		return (ft_syntax_error(curr->next->token));
	return (1);
}

int	ft_check_tokens(t_tokens *curr, int *open_p)
{
	while (curr)
	{
		if (curr->type >= RED_IN && curr->type <= APPEND)
		{
			if (!ft_check_redir(curr))
				return (0);
		}
		else if (curr->type >= AND && curr->type <= BACKGROUND)
		{
			if (!ft_check_operators(curr))
				return (0);
		}
		else if (curr->type == OPEN_PARENT || curr->type == CLOSE_PARENT)
		{
			if (!ft_check_parenthesis(curr, open_p))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

int	ft_parse(t_tokens *list)
{
	t_tokens	*curr;
	int			open_p;

	curr = list;
	open_p = 0;
	if (!curr)
		return (1);
	if ((curr->type >= AND && curr->type <= BACKGROUND)
		|| curr->type == CLOSE_PARENT)
		return (ft_syntax_error(curr->token));
	if (!ft_check_tokens(curr, &open_p))
		return (0);
	if (open_p != 0)
		return (ft_syntax_error("newline"));
	return (1);
}
