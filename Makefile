NAME = minishell

CC = cc

# CFLAGS = -g -Wall -Wextra -Werror
CFLAGS=

HEADER = -I ft_printf -I libft

RM = rm -rf

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_PATH = ./src
TREE_PATH = ./src/tree
ENV_PATH = /env
UTIL_PATH = /utils
FREE_PATH = /free
EXEC_PATH = /exec
BUILTINS_PATH = /builtins
EXPORT_PATH = /export
SIGNAL_PATH = /signal
REDIRECTION_PATH = ./src/redirection
FD_PATH =./src/fds

SRCS = $(SRCS_PATH)/main.c $(TREE_PATH)/create_tree.c $(REDIRECTION_PATH)/redirections.c $(TREE_PATH)/ast_utils.c $(TREE_PATH)/tree_execution.c $(SRCS_PATH)$(ENV_PATH)/env.c $(SRCS_PATH)$(ENV_PATH)/init.c \
		$(SRCS_PATH)$(ENV_PATH)/env_utils.c $(SRCS_PATH)$(UTIL_PATH)/ft_strncpy.c $(SRCS_PATH)$(FREE_PATH)/free_tree.c \
		$(SRCS_PATH)$(FREE_PATH)/free_all.c $(SRCS_PATH)$(FREE_PATH)/env_free.c $(SRCS_PATH)$(EXEC_PATH)/exec.c \
		$(SRCS_PATH)$(BUILTINS_PATH)$(EXPORT_PATH)/export_utils.c $(SRCS_PATH)$(BUILTINS_PATH)$(EXPORT_PATH)/ft_export.c \
		$(SRCS_PATH)$(BUILTINS_PATH)$(EXPORT_PATH)/export_add_utils.c $(SRCS_PATH)$(UTIL_PATH)/ft_strcmp.c \
		$(SRCS_PATH)$(UTIL_PATH)/ft_split_quoted.c $(SRCS_PATH)$(FREE_PATH)/cmd_free.c $(SRCS_PATH)$(BUILTINS_PATH)/ft_unset.c \
		$(SRCS_PATH)$(BUILTINS_PATH)/ft_exit.c $(SRCS_PATH)$(BUILTINS_PATH)/ft_pwd.c $(SRCS_PATH)$(UTIL_PATH)/count_tds.c \
		$(SRCS_PATH)$(BUILTINS_PATH)/ft_cd.c $(SRCS_PATH)$(BUILTINS_PATH)/ft_cd_utils.c $(SRCS_PATH)$(UTIL_PATH)/ft_strrchr.c $(SRCS_PATH)$(BUILTINS_PATH)/ft_echo.c \
		$(SRCS_PATH)$(UTIL_PATH)/ft_strnchr.c $(SRCS_PATH)$(UTIL_PATH)/ft_interpret.c $(SRCS_PATH)$(UTIL_PATH)/test_utils.c \
		$(SRCS_PATH)$(UTIL_PATH)/ft_cmd_utils.c $(SRCS_PATH)$(SIGNAL_PATH)/ft_handle_sig.c $(SRCS_PATH)$(UTIL_PATH)/prepare_cmd.c \
		$(SRCS_PATH)$(UTIL_PATH)/ft_find_cmd_path.c $(SRCS_PATH)$(BUILTINS_PATH)$(EXPORT_PATH)/export_utils2.c \
		$(SRCS_PATH)$(UTIL_PATH)/ft_insert_quotes.c $(SRCS_PATH)$(UTIL_PATH)/ft_remove_empty_args.c $(SRCS_PATH)$(UTIL_PATH)/prepare_cmd2.c \
		$(SRCS_PATH)$(UTIL_PATH)/ft_interpret_utils.c $(SRCS_PATH)$(UTIL_PATH)/prepare_cmd_helper.c $(SRCS_PATH)$(UTIL_PATH)/prepare_cmd_helper2.c \
		$(SRCS_PATH)$(UTIL_PATH)/ft_split_quoted_utils.c $(FD_PATH)/fd_utils.c $(FD_PATH)/fd.c $(REDIRECTION_PATH)/heredoc_utils.c $(TREE_PATH)/ast.c \
		$(TREE_PATH)/execute_redirections.c $(TREE_PATH)/execution_utils.c $(TREE_PATH)/execution_utils_2.c $(TREE_PATH)/execution_utils_3.c \
		$(TREE_PATH)/inits.c $(TREE_PATH)/pipe_utils.c $(TREE_PATH)/redirection_handling.c $(TREE_PATH)/tree_creation_utils.c \
		$(TREE_PATH)/tree_utils.c



OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
		${CC} ${CFLAGS} ${HEADER} -L${LIBFT_DIR} -lft ${OBJS} ${LIBFT} -lreadline -o ${NAME}

${LIBFT}:
		make -C ${LIBFT_DIR}

%.o: %.c
		${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean:
		make clean -C ${LIBFT_DIR}
		${RM} ${OBJS}

fclean: clean
		${RM} ${LIBFT}
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
