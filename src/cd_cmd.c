/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:55:51 by leandre           #+#    #+#             */
/*   Updated: 2026/05/05 09:30:42 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*node;
	char	*new_env;

	node = find_env_export(*env_list, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		new_env = malloc(ft_strlen(key) + ft_strlen(value) + 2);
		ft_strlcpy(new_env, key, ft_strlen(key) + 1);
		ft_strlcat(new_env, "=", ft_strlen(key) + 2);
		ft_strlcat(new_env, value, ft_strlen(key) + ft_strlen(value) + 2);
		add_update_export(env_list, new_env);
		free(new_env);
	}
}

static int	change_directory(char *args)
{
	char	*path;

	if (!args || args[0] == '\0')
	{
		path = getenv("HOME");
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		if (chdir(path) != 0)
			return (ft_putstr_fd("minishell: cd: ", 2), perror(path), 1);
	}
	else if (ft_strcmp(args, ".") == 0)
		return (0);
	else if (chdir(args) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	ft_cd(char *args, t_env **env_list)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return (1);
	if (change_directory(args) != 0)
		return (1);
	if (getcwd(new_pwd, PATH_MAX) != NULL)
	{
		update_env_var(env_list, "OLDPWD", old_pwd);
		update_env_var(env_list, "PWD", new_pwd);
	}
	return (0);
}

int	ft_run_cd(char **args, t_env **env_list)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (ft_cd(args[1], env_list));
}

void	print_error_heredoc(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
