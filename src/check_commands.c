/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:41:13 by leandre           #+#    #+#             */
/*   Updated: 2026/04/20 15:10:35 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_simple_command(t_tokens *list)
{
	t_tokens	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_count_commands(t_tokens *tokens)
{
	int			count;
	t_tokens	*tmp;

	count = 1;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_tokens	**ft_split_cmd(t_tokens *tokens)
{
	int			n_cmds;
	int			i;
	t_tokens	*tmp;
	t_tokens	**cmd_array;

	cmd_array = NULL;
	n_cmds = ft_count_commands(tokens);
	cmd_array = malloc(sizeof(t_tokens *) * (n_cmds + 1));
	if (!cmd_array)
		return (NULL);
	tmp = tokens;
	i = 0;
	cmd_array[i++] = tmp;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (tmp->next)
				cmd_array[i++] = tmp->next;
		}
		tmp = tmp->next;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}
