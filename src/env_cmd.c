/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:38:39 by leandre           #+#    #+#             */
/*   Updated: 2026/04/20 10:21:47 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *envv, int fd)
{
	if (envv->key)
	{
		ft_putstr_fd(envv->key, fd);
		ft_putchar_fd('=', fd);
	}
	if (envv->value)
	{
		ft_putstr_fd(envv->value, fd);
	}
	ft_putchar_fd('\n', fd);
}

void	only_env_cmd(t_env *env, int fd)
{
	while (env)
	{
		print_env(env, fd);
		env = env->next;
	}
}
