/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 13:04:26 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/07 13:08:30 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mini(t_mini *mini, t_tokens **cmd_array)
{
	free(mini->pid);
	free(cmd_array);
	ft_free_envp(&mini->env_list);
	ft_free_tokens(&mini->tokens);
}

void	free_cmd_array(t_tokens **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	ft_wait_all(t_mini *mini, int *pid, int n_cmds)
{
	int	j;
	int	sig;
	int	pid_status;

	j = 0;
	while (j < n_cmds)
	{
		waitpid(pid[j], &pid_status, 0);
		if (j == n_cmds - 1)
		{
			if (WIFEXITED(pid_status))
				mini->exit_code = WEXITSTATUS(pid_status);
			else if (WIFSIGNALED(pid_status))
			{
				sig = WTERMSIG(pid_status);
				if (sig == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
				else if (sig == SIGINT)
					ft_putstr_fd("\n", 2);
				mini->exit_code = 128 + sig;
			}
		}
		j++;
	}
}

void	ft_child_cleanup(t_mini *mini, char **args, char *path)
{
	if (args)
		ft_free_array(args);
	if (path)
		free(path);
	if (mini->env_array)
		ft_free_array(mini->env_array);
}

void	ft_clean_exit(char **args, t_mini *mini)
{
	ft_free_array(args);
	ft_free_envp(&mini->env_list);
	ft_free_tokens(&mini->tokens);
	exit(mini->exit_code);
}
