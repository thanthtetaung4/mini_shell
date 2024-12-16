NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
LIBFT_PATH = ./libft
LIBFT = ${LIBFT_PATH}/libft.a
SRCS = ft_printf.c  ft_putchar.c  ft_puthex.c  ft_puthexc.c  ft_putnbr.c  ft_putptr.c  ft_putstr.c  ft_putunbr.c
OBJS = ${SRCS:.c=.o}
all : ${NAME}
${NAME} : ${OBJS} ${LIBFT}
	cp $(LIBFT) ${NAME}
	${AR} $@ $^
${LIBFT} :
	make -C ${LIBFT_PATH} all
%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@
clean :
	make -C ${LIBFT_PATH} clean
	${RM} ${OBJS}
fclean : clean
	make -C ${LIBFT_PATH} fclean
	${RM} ${NAME}
re : fclean all
.PHONY : all clean fclean re
