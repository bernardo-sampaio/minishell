/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_redirections_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 13:12:54 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/07 13:13:14 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_delimiter(char *delimiter)
{
	if (delimiter[0] == '\\')
		return (0);
	return (1);
}

static char	*expand_variable(char *line, int *i, t_mini *mini, char *res)
{
	int		start;
	char	*var;
	char	*value;
	char	*safe;
	char	*tmp;

	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	var = ft_substr(line, start, *i - start);
	value = ft_get_env_value(var, mini);
	if (!value)
		safe = ft_strdup("");
	else
		safe = ft_strdup(value);
	tmp = ft_strjoin(res, safe);
	free(var);
	free(safe);
	free(res);
	return (tmp);
}

char	*ft_heredoc_expand_var(char *line, t_mini *mini)
{
	char	*res;
	char	*new_line;
	char	tmp1[2];
	int		i;

	res = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			res = expand_variable(line, &i, mini, res);
		}
		else
		{
			tmp1[0] = line[i];
			tmp1[1] = '\0';
			new_line = ft_strjoin(res, tmp1);
			free(res);
			res = new_line;
			i++;
		}
	}
	return (free(line), res);
}

int	check_line_delimiter(char *line, char *delimiter, t_mini *mini)
{
	if (!line)
	{
		print_error_heredoc(delimiter);
		return (0);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	if (g_signal == 130)
	{
		ft_free_envp(&mini->env_list);
		ft_free_tokens(&mini->tokens);
		exit(130);
	}
	return (1);
}
