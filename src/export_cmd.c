/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:21:18 by leandre           #+#    #+#             */
/*   Updated: 2026/04/27 14:05:07 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_env_export(t_env *curr, char *key)
{
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	append_tolist(t_env **env, t_env *new)
{
	t_env	*curr;

	if (!new)
		return ;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	curr = (*env);
	while (curr->next)
	{
		curr = curr->next;
	}
	curr->next = new;
}

void	add_update_export(t_env **env, char *envv)
{
	t_env	*curr;
	t_env	*tmp;

	tmp = get_env(envv, 1);
	if (!tmp)
		return ;
	curr = find_env_export((*env), tmp->key);
	if (curr)
	{
		if (curr->value)
			free(curr->value);
		curr->value = ft_strdup(tmp->value);
		ft_free_envp(&tmp);
	}
	else
		append_tolist(env, tmp);
}
