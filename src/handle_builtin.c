/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:57:11 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/06 17:40:53 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_run_unset(char **args, t_env **env_list)
{
	int	i;

	i = 0;
	if (args[1])
	{
		i = 1;
		while (args[i])
		{
			unset(*env_list, args[i]);
			i++;
		}
	}
	else
		unset(*env_list, NULL);
}

int	ft_run_export(char **args, t_env **env_list, int fd_out)
{
	int	i;

	i = 0;
	if (!args[1])
		only_export_cmd(*env_list, fd_out, 0);
	else
	{
		i = 1;
		while (args[i])
		{
			if (!ft_is_valid_identifier(args[i]))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (1);
			}
			add_update_export(env_list, args[i]);
			i++;
		}
	}
	return (0);
}

int	ft_run(char **args, t_mini *mini, int fd_out)
{
	if (!args || !args[0])
		return (1);
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args, fd_out));
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_run_cd(args, &mini->env_list));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(mini->env_list, fd_out));
	else if (!ft_strcmp(args[0], "env"))
		only_env_cmd(mini->env_list, fd_out);
	else if (!ft_strcmp(args[0], "export"))
		return (ft_run_export(args, &mini->env_list, fd_out));
	else if (!ft_strcmp(args[0], "unset"))
		ft_run_unset(args, &mini->env_list);
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, mini));
	return (0);
}

static void	setup_redirections(t_tokens *cmd, t_mini *mini, t_mini *min)
{
	min->fd1 = ft_red_out(cmd);
	if (min->fd1 > 2)
	{
		dup2(min->fd1, STDOUT_FILENO);
		close(min->fd1);
	}
	min->fd2 = ft_red_heredoc(mini, cmd);
	if (min->fd2 > 2)
	{
		dup2(min->fd2, STDOUT_FILENO);
		close(min->fd2);
	}
}

int	ft_run_builtin(t_tokens *cmd, t_mini *mini)
{
	t_mini	min;
	char	**args;
	int		fd_out;
	int		fd_in;

	fd_out = dup(STDOUT_FILENO);
	fd_in = dup(STDIN_FILENO);
	setup_redirections(cmd, mini, &min);
	args = ft_take_args(cmd);
	if (!args || !args[0])
	{
		dup2(fd_out, STDOUT_FILENO);
		dup2(fd_in, STDIN_FILENO);
		close(fd_out);
		close(fd_in);
		ft_free_array(args);
		return (0);
	}
	min.i = ft_run(args, mini, fd_out);
	ft_free_array(args);
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd_out);
	close(fd_in);
	return (min.i);
}
