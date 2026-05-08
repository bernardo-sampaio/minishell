/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:28:10 by bsampaio          #+#    #+#             */
/*   Updated: 2026/03/10 11:45:45 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_operator(char c)
{
	return ((c == '|' || c == '<' || c == '>' || c == '(' || c == ')'
			|| c == '&'));
}

int	ft_is_double_operator(char *line, size_t i)
{
	if (!line[i] || !line[i + 1])
		return (0);
	if (line[i] == '|' && line[i + 1] == '|')
		return (1);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (1);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (1);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (1);
	return (0);
}

t_tokens	*ft_get_double_operator(char *line, size_t i)
{
	if (line[i] == '>')
		return (ft_new_token(">>", APPEND));
	else if (line[i] == '<')
		return (ft_new_token("<<", HEREDOC));
	else if (line[i] == '&')
		return (ft_new_token("&&", AND));
	else if (line[i] == '|')
		return (ft_new_token("||", OR));
	return (NULL);
}

t_tokens	*ft_get_operator(char *line, size_t i)
{
	if (line[i] == '>')
		return (ft_new_token(">", RED_OUT));
	else if (line[i] == '<')
		return (ft_new_token("<", RED_IN));
	else if (line[i] == '|')
		return (ft_new_token("|", PIPE));
	else if (line[i] == '(')
		return (ft_new_token("(", OPEN_PARENT));
	else if (line[i] == ')')
		return (ft_new_token(")", CLOSE_PARENT));
	else if (line[i] == '&')
		return (ft_new_token("&", BACKGROUND));
	return (NULL);
}

int	ft_handle_operators(char *line, size_t i, t_tokens **list)
{
	t_tokens	*new;

	new = NULL;
	if (ft_is_double_operator(line, i))
	{
		new = ft_get_double_operator(line, i);
		if (!new)
			return (0);
		i += 2;
	}
	else
	{
		new = ft_get_operator(line, i);
		if (!new)
			return (0);
		i += 1;
	}
	ft_lstadd_back(list, new);
	return (i);
}
