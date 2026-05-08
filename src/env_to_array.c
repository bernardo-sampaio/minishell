/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:56:49 by bsampaio          #+#    #+#             */
/*   Updated: 2026/04/21 15:57:45 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	*ft_build_line(char *key, char *value)
{
	char	*tmp;
	char	*full_line;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	full_line = ft_strjoin(tmp, value);
	free(tmp);
	return (full_line);
}

char	**env_to_array(t_env *env_list)
{
	char	**array;
	int		i;
	int		size;

	size = ft_env_size(env_list);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env_list)
	{
		array[i] = ft_build_line(env_list->key, env_list->value);
		if (!array[i])
		{
			ft_free_array(array);
			return (NULL);
		}
		i++;
		env_list = env_list->next;
	}
	array[i] = NULL;
	return (array);
}
