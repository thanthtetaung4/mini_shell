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

SRCS = $(SRCS_PATH)/main.c $(TREE_PATH)/create_tree.c $(TREE_PATH)/visualizer.c $(TREE_PATH)/ast_utils.c $(TREE_PATH)/tree_execution.c $(SRCS_PATH)$(ENV_PATH)/env.c $(SRCS_PATH)$(ENV_PATH)/init.c \
		$(SRCS_PATH)$(ENV_PATH)/env_utils.c $(SRCS_PATH)$(UTIL_PATH)/ft_strncpy.c \
		$(SRCS_PATH)$(FREE_PATH)/free_all.c $(SRCS_PATH)$(FREE_PATH)/env_free.c $(SRCS_PATH)$(EXEC_PATH)/exec.c \
		$(SRCS_PATH)$(BUILTINS_PATH)$(EXPORT_PATH)/export_utils.c $(SRCS_PATH)$(BUILTINS_PATH)$(EXPORT_PATH)/ft_export.c \
		$(SRCS_PATH)$(BUILTINS_PATH)$(EXPORT_PATH)/export_add_utils.c $(SRCS_PATH)$(UTIL_PATH)/ft_strcmp.c \
		$(SRCS_PATH)$(UTIL_PATH)/ft_split_quoted.c $(SRCS_PATH)$(FREE_PATH)/cmd_free.c $(SRCS_PATH)$(BUILTINS_PATH)/ft_unset.c \
		$(SRCS_PATH)$(BUILTINS_PATH)/ft_exit.c



OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
		${CC} ${CFLAGS} ${HEADER} -L${LIBFT_DIR} -lft -lreadline ${OBJS} ${LIBFT} -o ${NAME}

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
