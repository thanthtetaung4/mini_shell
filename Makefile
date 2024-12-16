NAME = minishell

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

HEADER = -I ft_printf -I libft

RM = rm -rf

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_PATH = ./src

SRCS = $(SRCS_PATH)/main.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT} ${PRINTF}
		${CC} ${CFLAGS} ${HEADER} -L${LIBFT_DIR} -lft -L${PRINTF_DIR} ${OBJS} ${PRINTF} ${LIBFT} -lreadline -o ${NAME}

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
