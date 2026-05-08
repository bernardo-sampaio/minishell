/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:09:06 by leandre           #+#    #+#             */
/*   Updated: 2026/05/07 12:26:46 by bsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	WORD,
	AND,
	OR,
	PIPE,
	BACKGROUND,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND,
	OPEN_PARENT,
	CLOSE_PARENT
}								t_token_type;

typedef struct s_tokens
{
	char						*token;
	t_token_type				type;
	int							heredoc_fd;
	struct s_tokens				*next;
}								t_tokens;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
	int							exported;
}								t_env;

typedef struct s_mini
{
	t_env						*env_list;
	t_tokens					*tokens;
	t_tokens					**cmd_array;
	pid_t						*pid;
	char						*line;
	char						*value;
	char						*cmd;
	char						**args_cmd;
	char						**env_array;
	int							exit_code;
	int							fd[2];
	int							fd_prev;
	int							o_quote;
	int							i;
	int							j;
	int							fd1;
	int							fd2;
	int							n_cmds;
	int							error;
}								t_mini;

# define COLOR "\033[32m"

extern volatile sig_atomic_t	g_signal;

/* Tokenization and utils */

t_tokens						*ft_new_token(char *token, t_token_type type);
t_tokens						*ft_get_tokens(char *line);
size_t							ft_tokenize_step(char *line, size_t i,
									t_tokens **list);
void							ft_free_tokens(t_tokens **list);
int								ft_is_operator(char c);
int								ft_is_double_operator(char *line, size_t i);
int								ft_handle_operators(char *line, size_t i,
									t_tokens **list);

/* Parse and utils */

int								ft_parse(t_tokens *list);
int								ft_check_quotes(char *line);
int								ft_syntax_error(char *token);

/* Expansion and utils */

char							*ft_expander(char *s, t_mini *mini);
void							ft_apply_expansions(t_mini *mini);
char							*ft_get_env_value(char *var_name, t_mini *mini);
char							*ft_expand_var(char *s, t_mini *mini);
int								ft_var_name_len(char *s);

/* Execuctions and utils */

int								ft_is_simple_command(t_tokens *list);
int								ft_count_commands(t_tokens *tokens);
t_tokens						**ft_split_cmd(t_tokens *tokens);
char							**ft_take_args(t_tokens *token);
void							free_mini(t_mini *mini, t_tokens **cmd_array);

void							free_cmd_array(t_tokens **arr);
char							*ft_found_path(char *cmd, char **envp);
void							ft_lstadd_back(t_tokens **list, t_tokens *new);
char							*ft_try_paths(char **paths, char *tmp_cmd);
char							*found_path(t_env *env, char *cmd);
void							ft_error_exit(char *cmd, char *path, int code);
void							ft_execute_external(t_mini *mini,
									t_tokens *token);
void							ft_exec_built(t_mini *mini, t_tokens *cmd);
void							ft_exec_cmds(t_mini *mini, t_tokens *tokens);
void							ft_wait_all(t_mini *mini, int *pid, int n_cmds);
void							ft_free_line(t_mini *mini);
int								has_command(t_tokens *tokens);
void							ft_init_mini(t_mini *mini, char **env);
int								handle_line(t_mini *mini);
void							ft_switch_exec(t_mini *mini, t_tokens *tmp);
void							free_mini(t_mini *mini, t_tokens **cmd_array);
void							free_cmd_array(t_tokens **arr);
void							ft_wait_all(t_mini *mini, int *pid, int n_cmds);
void							ft_child_cleanup(t_mini *mini, char **args,
									char *path);
void							ft_clean_exit(char **args, t_mini *mini);
void							ft_free_line(t_mini *mini);
void							print_error_heredoc(char *delimiter);

/*Buit-in and utils*/

int								ft_is_builtin(char *cmd);
int								ft_run_builtin(t_tokens *cmd, t_mini *mini);
int								ft_pwd(t_env *envp_list, int fd);
int								ft_cd(char *args, t_env **env_list);
int								ft_run_cd(char **args, t_env **env_list);
int								ft_echo(char **args, int fd);
void							unset(t_env *head, char *name);
int								ft_exit(char **args, t_mini *mini);
void							append_tolist(t_env **env, t_env *new);
void							only_env_cmd(t_env *env, int fd);
void							only_export_cmd(t_env *envv, int fd, int exp);
void							add_update_export(t_env **env, char *envv);
void							print_env_export(t_env *envv, int fd);
char							**env_to_array(t_env *env_list);
void							print_only_exported(t_env *env, int fd);
void							ft_free_envp(t_env **list);
void							ft_exec_export(t_env **envp_list, char **args,
									int fd);

t_env							*find_env_export(t_env *curr, char *key);
t_env							*init_env(char **env);
t_env							*get_env(char *env, int exp);
t_env							*free_env_list(t_env *head);
t_env							*free_env_node(t_env *node);
void							bubble_sort(t_env **arr, int count);
t_env							**sort_env(t_env *env);

/* Signals and utils */
void							sigint_heredoc(int sig);
void							close_sig(int signum);
void							check_sig(t_mini *mini);
void							setup_signals(void);
void							setup_signal_heredoc(void);
void							ft_free_array(char **paths);
char							*found_path(t_env *env, char *cmd);

/* Redirections and utils*/

int								ft_heredoc(t_mini *mini, char *delimiter);
int								ft_red_in(char *file);
int								ft_open_single_out(t_tokens *tmp);
int								ft_red_heredoc(t_mini *mini, t_tokens *token);
int								ft_red_out(t_tokens *token);
int								ft_is_valid_identifier(char *str);
int								ft_open_single_out(t_tokens *tmp);
int								ft_apply_all_redirections(t_tokens *tokens);
int								ft_process_all_heredocs(t_mini *mini,
									t_tokens *tokens);
void							print_error_heredoc(char *delimiter);
int								check_line_delimiter(char *line,
									char *delimiter, t_mini *mini);
char							*ft_heredoc_expand_var(char *line,
									t_mini *mini);
int								ft_check_delimiter(char *delimiter);

#endif
