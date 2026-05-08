/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:18:14 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/05 09:24:45 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_var_name_len(char *s)
{
	int	i;

	i = 1;
	if (s[i] && (ft_isdigit(s[i]) || s[i] == '?'))
		i++;
	else
	{
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
	}
	return (i);
}

static int	ft_getvar_len(char *s, int *i, t_mini *mini)
{
	char	*value;
	int		var_len;

	value = ft_expand_var(&s[*i], mini);
	var_len = ft_strlen(value);
	free(value);
	*i += ft_var_name_len(&s[*i]);
	return (var_len);
}

int	ft_get_final_len(char *s, t_mini *mini)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && (!mini->o_quote
				|| mini->o_quote == s[i]))
		{
			if (!mini->o_quote)
				mini->o_quote = s[i];
			else if (s[i] == mini->o_quote)
				mini->o_quote = 0;
			i++;
		}
		else if (s[i] == '$' && mini->o_quote != '\'' && s[i + 1]
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
			len += ft_getvar_len(s, &i, mini);
		else if (++len)
			i++;
	}
	return (len);
}

void	ft_process_expansion(char *s, char *str, t_mini *mini)
{
	while (s[mini->i])
	{
		if ((s[mini->i] == '\'' || s[mini->i] == '"') && (!mini->o_quote
				|| mini->o_quote == s[mini->i]))
		{
			if (!mini->o_quote)
				mini->o_quote = s[mini->i];
			else
				mini->o_quote = 0;
			mini->i++;
		}
		else if (s[mini->i] == '$' && mini->o_quote != '\'' && s[mini->i + 1]
			&& (ft_isalnum(s[mini->i + 1]) || s[mini->i + 1] == '_' || s[mini->i
					+ 1] == '?'))
		{
			mini->value = ft_expand_var(&s[mini->i], mini);
			ft_strlcpy(&str[mini->j], mini->value, ft_strlen(mini->value) + 1);
			mini->j += ft_strlen(mini->value);
			free(mini->value);
			mini->i += ft_var_name_len(&s[mini->i]);
		}
		else
			str[mini->j++] = s[mini->i++];
	}
	str[mini->j] = '\0';
}

char	*ft_expander(char *s, t_mini *mini)
{
	char	*str;

	mini->value = NULL;
	str = malloc((ft_get_final_len(s, mini) + 1));
	if (!str)
		return (NULL);
	mini->i = 0;
	mini->j = 0;
	mini->o_quote = 0;
	ft_process_expansion(s, str, mini);
	return (str);
}
