# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsampaio <bsampaio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/13 09:02:30 by leandre           #+#    #+#              #
#    Updated: 2026/05/05 13:24:04 by bsampaio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
RDLINEFLAG = -lreadline
LIBFT_DIR = libft
PIPEX_DIR = pipex
PIPEX = $(PIPEX_DIR)
LIBFT= $(LIBFT_DIR)/libft.a
SRCS = src/main.c src/check_commands.c\
		src/tokens.c src/handle_operators.c src/parse.c\
		src/expander.c src/signals.c src/pwd_cmd.c src/envp.c\
		src/processing_env.c src/export_cmd.c src/print_export.c\
		src/env_cmd.c src/cd_cmd.c src/echo_cmd.c src/unset_cmd.c\
		src/exec_cmd.c src/handle_builtin.c src/utils.c src/redirection.c\
		src/exit_cmd.c src/expander_utils.c src/env_sort.c\
		src/redirections_utils.c src/env_to_array.c src/exec_utils.c\
		src/minishell_utils.c src/executor.c src/cleanup_exec.c\
		src/aux_redirections_utils.c
		
OBJS = $(SRCS:.c=.o)
HEADER = minishell.h

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(RDLINEFLAG) -o $(NAME)
 
$(OBJS): $(HEADER)

clean: 
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: re fclean clean all
