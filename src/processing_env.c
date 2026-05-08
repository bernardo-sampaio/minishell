/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:10:22 by leandre           #+#    #+#             */
/*   Updated: 2026/04/20 14:21:29 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*free_env_node(t_env *node)
{
	if (!node)
		return (NULL);
	free(node->key);
	free(node->value);
	free(node);
	return (NULL);
}

t_env	*free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free_env_node(head);
		head = tmp;
	}
	return (NULL);
}

t_env	*get_env(char *env, int exp)
{
	char	*equal;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (exp == 1)
		new->exported = 1;
	else
		new->exported = 0;
	equal = ft_strchr(env, '=');
	if (equal)
	{
		new->key = ft_substr(env, 0, equal - env);
		new->value = ft_strdup(equal + 1);
	}
	else
	{
		new->key = ft_strdup(env);
		new->value = ft_strdup("");
	}
	if (!new->key || !new->value)
		return (free_env_node(new));
	new->next = NULL;
	return (new);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	int		i;

	i = 0;
	head = NULL;
	tail = NULL;
	while (env[i])
	{
		node = get_env(env[i], 0);
		if (!node)
			return (free_env_list(head));
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (head);
}

void	ft_free_line(t_mini *mini)
{
	if (mini->line)
	{
		free(mini->line);
		mini->line = NULL;
	}
}
