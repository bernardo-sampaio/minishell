/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:13:45 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/07 12:46:36 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run_heredoc_child(t_mini *mini, char *delimiter, int fd[2])
{
	char	*line;
	int		exp;

	setup_signal_heredoc();
	close(fd[0]);
	exp = ft_check_delimiter(delimiter);
	if (delimiter[0] && delimiter[1] && delimiter[0] == '\\')
		delimiter = delimiter + 1;
	while (1)
	{
		line = readline("> ");
		if (!check_line_delimiter(line, delimiter, mini))
			break ;
		if (exp)
			line = ft_heredoc_expand_var(line, mini);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	ft_free_envp(&mini->env_list);
	ft_free_tokens(&mini->tokens);
	exit(0);
}

int	ft_heredoc(t_mini *mini, char *delimiter)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		run_heredoc_child(mini, delimiter, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		close(fd[0]);
		mini->exit_code = WEXITSTATUS(status);
		return (-1);
	}
	mini->exit_code = status;
	return (fd[0]);
}

int	ft_process_all_heredocs(t_mini *mini, t_tokens *tokens)
{
	t_tokens	*tmp;
	int			fd;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			fd = ft_heredoc(mini, tmp->next->token);
			if (fd == -1)
				return (-1);
			tmp->heredoc_fd = fd;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_red_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		return (-1);
	}
	return (fd);
}

int	ft_open_single_out(t_tokens *tmp)
{
	int	fd;

	if (tmp->type == RED_OUT)
		fd = open(tmp->next->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(tmp->next->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(tmp->next->token);
	}
	return (fd);
}
