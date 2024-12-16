NAME = minishell

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

HEADER = -I ft_printf -I libft

RM = rm -rf

LIBFT_DIR = ./ft_printf/libft

LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ./ft_printf

PRINTF = $(PRINTF_DIR)/libftprintf.a

SRCS_PATH = ./src

SRCS = $(SRCS_PATH)/main.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT} ${PRINTF}
		${CC} ${CFLAGS} ${HEADER} -L${LIBFT_DIR} -lft -L${PRINTF_DIR} -lreadline ${OBJS} ${PRINTF} ${LIBFT} -o ${NAME}

${LIBFT}:
		make -C ${LIBFT_DIR}

${PRINTF}:
		make -C ${PRINTF_DIR}

%.o: %.c
		${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean:
		make clean -C ${LIBFT_DIR}
		make clean -C ${PRINTF_DIR}
		${RM} ${OBJS}

fclean: clean
		${RM} ${LIBFT}
		${RM} ${PRINTF}
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
