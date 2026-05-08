/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:47:39 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/05 10:44:09 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_apply_expansions(t_mini *mini)
{
	t_tokens	*tmp;
	char		*expanded_str;

	tmp = mini->tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			expanded_str = ft_expander(tmp->token, mini);
			free(tmp->token);
			tmp->token = expanded_str;
		}
		tmp = tmp->next;
	}
}

int	ft_check_quotes(char *line)
{
	int	in_quote;
	int	i;

	in_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (!in_quote)
				in_quote = line[i];
			else if (in_quote == line[i])
				in_quote = 0;
		}
		i++;
	}
	if (in_quote)
		return (0);
	return (1);
}

int	ft_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	ft_free_array(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}
