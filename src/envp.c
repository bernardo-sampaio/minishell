/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:25:23 by bsampaio          #+#    #+#             */
/*   Updated: 2026/04/27 15:33:38 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_envp(t_env **list)
{
	t_env	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->key)
			free((*list)->key);
		if ((*list)->value)
			free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	ft_envadd_back(t_env **list, t_env *new)
{
	t_env	*last;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

void static	ft_free_util(t_env *new)
{
	free(new->key);
	free(new->value);
	free(new);
}

t_env	*ft_new_envp_node(char *envp)
{
	t_env	*new;
	char	*pos_equal;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	pos_equal = ft_strchr(envp, '=');
	if (pos_equal)
	{
		new->key = ft_substr(envp, 0, pos_equal - envp);
		new->value = ft_strdup(pos_equal + 1);
	}
	else
	{
		new->key = ft_strdup(envp);
		new->value = ft_strdup("");
	}
	if (!new->key || !new->value)
	{
		ft_free_util(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*ft_init_env(char **envp)
{
	size_t	i;
	t_env	*list;
	t_env	*new_node;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = ft_new_envp_node(envp[i]);
		if (!new_node)
		{
			ft_free_envp(&list);
			return (NULL);
		}
		ft_envadd_back(&list, new_node);
		i++;
	}
	return (list);
}
