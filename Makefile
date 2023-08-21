SUBDIR	= srcs

OBJDIR	= objs

SRCS	=	${SUBDIR}/minishell.c\
			${SUBDIR}/ms_tokenize.c\
			${SUBDIR}/ms_path_parse.c\
			${SUBDIR}/ms_error_codes.c\
			${SUBDIR}/ms_tokenize_utils.c\

OBJ		= $(patsubst ${SUBDIR}/%.c, ${OBJDIR}/%.o, ${SRCS})

NAME	= minishell

CFLAGS	= -Wall -Werror -Wextra -O2

LFLAGS = -Llibft -lft

CC = gcc

${NAME}:	${OBJ}
			make -C libft all
			${CC} ${OBJ} -o ${NAME} ${LFLAGS}

${OBJDIR}/%.o:	${SUBDIR}/%.c | ${OBJDIR}
				${CC} ${CFLAGS} -c $< -o $@

${OBJDIR}:
		mkdir -p $@

all:	${NAME}

debug:
		make -C libft all
		${CC} -D DEBUG=1 ${SRCS} -o ${NAME} ${LFLAGS} -g3 -fsanitize=address

clean:
		rm -rf ${OBJDIR}
		make -C libft clean

fclean:	clean
		rm -f ${NAME}
		rm -f libft/libft.a

re:		fclean all

.PHONY: all fclean clean re