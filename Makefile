NAME = minishell

CC = cc

# CFLAGS = -g -Wall -Wextra -Werror
CFLAGS=

HEADER = -I ft_printf -I libft

RM = rm -rf

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_PATH = ./src

ENV_PATH = /env

UTIL_PATH = /utils

FREE_PATH = /free

EXEC_PATH = /exec

SRCS = $(SRCS_PATH)/main.c $(SRCS_PATH)$(ENV_PATH)/env.c $(SRCS_PATH)$(ENV_PATH)/init.c \
		$(SRCS_PATH)$(ENV_PATH)/env_utils.c $(SRCS_PATH)$(UTIL_PATH)/ft_strncpy.c \
		$(SRCS_PATH)$(FREE_PATH)/free_all.c $(SRCS_PATH)$(EXEC_PATH)/exec.c \

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
