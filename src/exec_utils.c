/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:26:37 by bsampaio          #+#    #+#             */
/*   Updated: 2026/05/06 18:32:11 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_try_paths(char **paths, char *tmp_cmd)
{
	int		i;
	char	*tokens;

	i = 0;
	while (paths && paths[i])
	{
		tokens = ft_strjoin(paths[i], tmp_cmd);
		if (access(tokens, X_OK) == 0)
			return (tokens);
		free(tokens);
		i++;
	}
	return (NULL);
}

char	*found_path(t_env *env, char *cmd)
{
	t_env	*find;
	char	**paths;
	char	*res;
	char	*tmp_cmd;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	tmp_cmd = ft_strjoin("/", cmd);
	find = find_env_export(env, "PATH");
	if (find && find->value)
	{
		paths = ft_split(find->value, ':');
		res = ft_try_paths(paths, tmp_cmd);
		ft_free_array(paths);
		free(tmp_cmd);
		return (res);
	}
	free(tmp_cmd);
	return (NULL);
}

static void	handle_path_not_found(t_mini *mini, t_tokens *token, char **args)
{
	if (token->token[0] == '/' || token->token[0] == '.')
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->token);
	}
	else
	{
		ft_putstr_fd(token->token, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	ft_free_array(args);
	ft_free_envp(&mini->env_list);
	ft_free_tokens(&mini->tokens);
	free_cmd_array(mini->cmd_array);
	free(mini->pid);
	exit(127);
}

static void	handle_invalid_path(t_mini *mini, t_tokens *token, char **args,
		char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->token, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		ft_free_array(args);
		ft_free_envp(&mini->env_list);
		ft_free_tokens(&mini->tokens);
		free_cmd_array(mini->cmd_array);
		free(mini->pid);
		free(path);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->token);
		ft_free_array(args);
		free_mini(mini, mini->cmd_array);
		free(path);
		exit(126);
	}
}

void	ft_execute_external(t_mini *mini, t_tokens *token)
{
	char	**args;
	char	*path;

	args = ft_take_args(token);
	path = found_path(mini->env_list, token->token);
	if (!path)
		handle_path_not_found(mini, token, args);
	handle_invalid_path(mini, token, args, path);
	mini->env_array = env_to_array(mini->env_list);
	execve(path, args, mini->env_array);
	ft_free_array(mini->env_array);
	ft_free_array(args);
	free(path);
	ft_putstr_fd(token->token, 2);
	ft_putstr_fd(": execution failed\n", 2);
	ft_free_envp(&mini->env_list);
	ft_free_tokens(&mini->tokens);
	free(mini->pid);
	exit(126);
}
