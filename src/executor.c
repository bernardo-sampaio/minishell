/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:19:07 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/05 09:12:48 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_command(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*prev;

	prev = NULL;
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type >= RED_IN && tmp->type <= APPEND)
		{
			if (tmp->next)
				tmp = tmp->next->next;
		}
		else if (tmp->type == WORD)
			return (1);
		else
			tmp = tmp->next;
	}
	return (0);
}

void	ft_init_mini(t_mini *mini, char **env)
{
	mini->env_list = init_env(env);
	mini->tokens = NULL;
	mini->line = NULL;
	mini->exit_code = 0;
	mini->o_quote = 0;
	mini->i = 0;
	mini->j = 0;
	mini->value = NULL;
}

int	handle_line(t_mini *mini)
{
	if (!mini->line)
	{
		ft_putstr_fd("exit\n", 1);
		return (-1);
	}
	if (mini->line[0] != '\0')
		add_history(mini->line);
	if (!ft_check_quotes(mini->line))
	{
		ft_putstr_fd("minishell: error: unclosed quotes!\n", 2);
		mini->exit_code = 2;
		return (0);
	}
	mini->tokens = ft_get_tokens(mini->line);
	if (!ft_parse(mini->tokens))
	{
		ft_free_tokens(&mini->tokens);
		mini->exit_code = 2;
		return (0);
	}
	return (1);
}

void	ft_switch_exec(t_mini *mini, t_tokens *tmp)
{
	if (ft_is_simple_command(tmp) && ft_is_builtin(tmp->token))
		ft_exec_built(mini, tmp);
	else
		ft_exec_cmds(mini, tmp);
}
