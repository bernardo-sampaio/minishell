/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:02:32 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/07 12:50:05 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal = 0;

static int	ft_prepare_line(t_mini *mini)
{
	int	res;

	setup_signals();
	mini->line = readline("minishell$ ");
	check_sig(mini);
	res = handle_line(mini);
	if (res == -1)
		return (-1);
	if (res == 0)
	{
		ft_free_line(mini);
		return (0);
	}
	ft_apply_expansions(mini);
	return (1);
}

static int	ft_process_heredocs(t_mini *mini)
{
	if (ft_process_all_heredocs(mini, mini->tokens) == -1)
	{
		check_sig(mini);
		ft_free_tokens(&mini->tokens);
		ft_free_line(mini);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		return (0);
	}
	return (1);
}

static void	execute_commands(t_mini *mini)
{
	t_tokens	*tmp;
	t_tokens	*cmd_token;

	tmp = mini->tokens;
	while (tmp && tmp->token && tmp->token[0] == '\0')
		tmp = tmp->next;
	if (tmp && tmp->token)
	{
		cmd_token = tmp;
		while (cmd_token && (cmd_token->type >= RED_IN
				&& cmd_token->type <= APPEND))
		{
			if (cmd_token->next)
				cmd_token = cmd_token->next->next;
			else
				break ;
		}
		ft_switch_exec(mini, tmp);
	}
	ft_free_tokens(&mini->tokens);
	ft_free_line(mini);
}

void	ft_run_minishell(t_mini *mini)
{
	int	res;

	while (1)
	{
		res = ft_prepare_line(mini);
		if (res == -1)
			break ;
		if (res == 0)
			continue ;
		if (!ft_process_heredocs(mini))
			continue ;
		execute_commands(mini);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	if (ac != 1 || !av || !env)
		return (1);
	ft_init_mini(&mini, env);
	ft_run_minishell(&mini);
	ft_free_envp(&mini.env_list);
	rl_clear_history();
	return (mini.exit_code);
}
