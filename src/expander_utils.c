/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:28:00 by bsampaio          #+#    #+#             */
/*   Updated: 2026/04/21 13:28:08 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env_value(char *var_name, t_mini *mini)
{
	t_env	*tmp;

	tmp = mini->env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var_name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_expand_var(char *s, t_mini *mini)
{
	int		i;
	char	*var_name;
	char	*value;
	char	*env_val;

	if (!s || s[0] != '$')
		return (NULL);
	i = 0;
	i += ft_var_name_len(&s[i]);
	var_name = ft_substr(s, 1, i - 1);
	if (!ft_strcmp(var_name, "?"))
		value = ft_itoa(mini->exit_code);
	else
	{
		env_val = ft_get_env_value(var_name, mini);
		if (env_val)
			value = ft_strdup(env_val);
		else
			value = NULL;
	}
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}
