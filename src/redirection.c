/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:42:17 by leandre           #+#    #+#             */
/*   Updated: 2026/05/05 09:32:05 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_red_out(t_tokens *token)
{
	t_tokens	*tmp;
	int			fd;

	tmp = token;
	fd = -1;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == RED_OUT || tmp->type == APPEND)
		{
			if (fd != -1)
				close(fd);
			if (tmp->type == RED_OUT)
				fd = open(tmp->next->token, O_CREAT | O_WRONLY | O_TRUNC);
			if (tmp->type == APPEND)
				fd = open(tmp->next->token, O_CREAT | O_WRONLY | O_APPEND);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tmp->next->token);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (fd);
}

int	ft_red_heredoc(t_mini *mini, t_tokens *token)
{
	t_tokens	*tmp;
	int			fd;

	fd = -1;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == RED_IN)
		{
			if (fd != -1)
				close(fd);
			fd = ft_red_in(tmp->next->token);
		}
		else if (tmp->type == HEREDOC)
		{
			if (fd != -1)
				close(fd);
			fd = ft_heredoc(mini, tmp->next->token);
		}
		tmp = tmp->next;
	}
	return (fd);
}

int	handle_input(t_tokens *tmp)
{
	int	fd;

	if (tmp->type == RED_IN)
		fd = ft_red_in(tmp->next->token);
	else
	{
		if (tmp->heredoc_fd == -1)
			return (-1);
		fd = tmp->heredoc_fd;
	}
	if (fd == -1)
		return (-1);
	dup2(fd, STDIN_FILENO);
	if (fd > 2)
		close(fd);
	return (0);
}

int	handle_output(t_tokens *tmp)
{
	int	fd;

	fd = ft_open_single_out(tmp);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_apply_all_redirections(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == RED_IN || tmp->type == HEREDOC)
		{
			if (handle_input(tmp) == -1)
				return (-1);
		}
		else if (tmp->type == RED_OUT || tmp->type == APPEND)
		{
			if (handle_output(tmp) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
