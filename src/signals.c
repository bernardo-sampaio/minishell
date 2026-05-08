/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:03:04 by leandre           #+#    #+#             */
/*   Updated: 2026/05/07 12:37:42 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_sig(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, close_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	check_sig(t_mini *mini)
{
	if (g_signal == 130)
	{
		mini->exit_code = g_signal;
		g_signal = 0;
	}
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = 130;
	rl_done = 1;
	write(1, "\n", 1);
	ioctl(STDIN_FILENO, TIOCSTI, "  ");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
