/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:15:26 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/06 18:49:35 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_exit_error(char *args, t_mini *mini)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	mini->exit_code = 2;
}

int	ft_isnum_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_limit(unsigned long long res, int neg, int *error)
{
	if ((neg == 1 && res > 9223372036854775807ULL) || (neg == -1
			&& res > 9223372036854775808ULL))
		*error = 1;
	return (0);
}

long long	ft_atoll_exit(const char *str, int *error)
{
	unsigned long long	res;
	int					neg;
	int					i;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		ft_check_limit(res, neg, error);
		i++;
	}
	return ((long long)res * neg);
}

int	ft_exit(char **args, t_mini *mini)
{
	long long	res;

	mini->error = 0;
	if (!args[1])
	{
		ft_putstr_fd("exit\n", 1);
		ft_clean_exit(args, mini);
	}
	res = ft_atoll_exit(args[1], &mini->error);
	if (!ft_isnum_str(args[1]) || mini->error)
	{
		ft_exit_error(args[1], mini);
		ft_clean_exit(args, mini);
	}
	if (args[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		mini->exit_code = 1;
		return (mini->exit_code);
	}
	ft_putendl_fd("exit", 1);
	mini->exit_code = res;
	ft_clean_exit(args, mini);
	return (mini->exit_code);
}
