/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 12:04:19 by leandre           #+#    #+#             */
/*   Updated: 2026/05/07 12:31:12 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_built(t_mini *mini, t_tokens *cmd)
{
	int	stdin;
	int	stdout;

	if (!has_command(cmd))
	{
		if (ft_apply_all_redirections(cmd) == -1)
			mini->exit_code = 1;
		else
			mini->exit_code = 0;
		return ;
	}
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (ft_apply_all_redirections(cmd) == -1)
		mini->exit_code = 1;
	else
		mini->exit_code = ft_run_builtin(cmd, mini);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
}

static void	setup_child(t_mini *mini, t_tokens **cmd_array, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (mini->fd_prev != -1)
	{
		dup2(mini->fd_prev, STDIN_FILENO);
		close(mini->fd_prev);
	}
	if (cmd_array[i + 1])
	{
		dup2(mini->fd[1], STDOUT_FILENO);
		close(mini->fd[1]);
		close(mini->fd[0]);
	}
	if (ft_apply_all_redirections(cmd_array[i]) == -1)
	{
		free_mini(mini, cmd_array);
		exit(1);
	}
}

static void	ft_handle_child(t_mini *mini, t_tokens **cmd_array, int i)
{
	setup_child(mini, cmd_array, i);
	if (!has_command(cmd_array[i]))
	{
		free_mini(mini, cmd_array);
		exit(0);
	}
	if (ft_is_builtin(cmd_array[i]->token))
	{
		signal(SIGPIPE, SIG_IGN);
		mini->exit_code = ft_run_builtin(cmd_array[i], mini);
		free_mini(mini, cmd_array);
		exit(mini->exit_code);
	}
	ft_execute_external(mini, cmd_array[i]);
}

static void	init_exec_data(t_mini *mini, t_tokens *tokens)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	mini->cmd_array = ft_split_cmd(tokens);
	mini->n_cmds = 0;
	while (mini->cmd_array[mini->n_cmds])
		mini->n_cmds++;
	mini->pid = malloc(sizeof(pid_t) * mini->n_cmds);
	if (!mini->pid)
		return ;
	mini->fd_prev = -1;
}

void	ft_exec_cmds(t_mini *mini, t_tokens *tokens)
{
	int	i;

	i = -1;
	init_exec_data(mini, tokens);
	while (mini->cmd_array[++i])
	{
		if (mini->cmd_array[i + 1])
			pipe(mini->fd);
		mini->pid[i] = fork();
		if (mini->pid[i] == 0)
			ft_handle_child(mini, mini->cmd_array, i);
		if (mini->fd_prev != -1)
			close(mini->fd_prev);
		if (mini->cmd_array[i + 1])
		{
			mini->fd_prev = mini->fd[0];
			close(mini->fd[1]);
		}
	}
	ft_wait_all(mini, mini->pid, mini->n_cmds);
	if (mini->pid)
		free(mini->pid);
	mini->pid = NULL;
	free_cmd_array(mini->cmd_array);
	setup_signals();
}
