/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:38:48 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/05 09:33:18 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	**sort_env(t_env *env)
{
	t_env	**temp_arr;
	t_env	*curr;
	int		size;
	int		i;

	size = 0;
	curr = env;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	temp_arr = malloc(sizeof(t_env *) * (size + 1));
	if (!temp_arr)
		return (NULL);
	i = 0;
	curr = env;
	while (curr)
	{
		temp_arr[i] = curr;
		curr = curr->next;
		i++;
	}
	temp_arr[i] = NULL;
	return (temp_arr);
}

static void	check_and_swap(t_env **arr, int j, bool *swappend)
{
	t_env	*tmp;

	if (arr[j] && arr[j + 1] && arr[j]->key && arr[j + 1]->key)
	{
		if ((ft_strcmp(arr[j]->key, arr[j + 1]->key)) > 0)
		{
			tmp = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = tmp;
			*swappend = true;
		}
	}
}

void	bubble_sort(t_env **arr, int count)
{
	int		i;
	int		j;
	bool	swappend;

	if (!arr || count < 2)
		return ;
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		swappend = false;
		while (j < count - i - 1)
		{
			check_and_swap(arr, j, &swappend);
			j++;
		}
		if (!swappend)
			break ;
		i++;
	}
}
