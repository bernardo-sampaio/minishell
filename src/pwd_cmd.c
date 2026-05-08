/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:23:14 by leandre           #+#    #+#             */
/*   Updated: 2026/04/27 11:42:46 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_env *envp_list, int fd)
{
	char	*path;
	t_env	*node;

	node = find_env_export(envp_list, "PWD");
	if (node && node->value)
	{
		ft_putstr_fd(node->value, fd);
		ft_putstr_fd("\n", fd);
		return (0);
	}
	path = malloc(PATH_MAX);
	if (!path)
		return (1);
	if (getcwd(path, PATH_MAX) != NULL)
	{
		ft_putstr_fd(path, fd);
		ft_putstr_fd("\n", fd);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}
