/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:25:03 by leandre           #+#    #+#             */
/*   Updated: 2026/05/01 09:54:36 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_env *head, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = head;
	if (tmp != NULL && (ft_strcmp(tmp->key, name) == 0))
	{
		head = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (tmp && (ft_strcmp(tmp->key, name) != 0))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}
