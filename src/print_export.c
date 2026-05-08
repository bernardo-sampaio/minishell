/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:54:45 by leandre           #+#    #+#             */
/*   Updated: 2026/05/06 17:44:03 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (-(*s2));
	if (s1 && !s2)
		return (*s1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_env_export(t_env *envv, int fd)
{
	char	*dcl;

	if (!envv || !envv->key)
		return ;
	dcl = "declare -x ";
	ft_putstr_fd(dcl, fd);
	ft_putstr_fd(envv->key, fd);
	if (envv->value)
	{
		ft_putchar_fd('=', fd);
		ft_putchar_fd('"', fd);
		ft_putstr_fd(envv->value, fd);
		ft_putchar_fd('"', fd);
	}
	ft_putchar_fd('\n', fd);
}

static int	ft_count_env(t_env *tmp)
{
	int	count;

	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	only_export_cmd(t_env *envv, int fd, int exp)
{
	t_env	**curr;
	int		count;
	int		i;

	i = 0;
	curr = sort_env(envv);
	if (!curr)
		return ;
	count = ft_count_env(envv);
	bubble_sort(curr, count);
	while (i < count)
	{
		if (curr[i]->exported == 1 && exp == 1)
		{
			if (!ft_isupper(curr[i]->key[0]))
				print_env_export(curr[i], fd);
		}
		else if ((curr[i]->exported == 0 && exp == 0) || (curr[i]->exported == 1
				&& ft_isupper(curr[i]->key[0])))
			print_env_export(curr[i], fd);
		i++;
	}
	free(curr);
}
