SUBDIR	= srcs

OBJDIR	= objs

SRCS	=	${SUBDIR}/minishell.c\
		${SUBDIR}/exec/ms_exec.c\
		${SUBDIR}/exec/ms_pathify.c\
		${SUBDIR}/exec/ms_builtins_1.c\
		${SUBDIR}/exec/ms_builtins_2.c\
		${SUBDIR}/piping/ms_tokenize.c\
		${SUBDIR}/piping/ms_heredocs.c\
		${SUBDIR}/piping/ms_pipework.c\
		${SUBDIR}/parsing/ms_parsing.c\
		${SUBDIR}/parsing/ms_env_init.c\
		${SUBDIR}/parsing/ms_env_utils.c\
		${SUBDIR}/parsing/ms_parsing_2.c\
		${SUBDIR}/utils/ms_error_codes.c\
		${SUBDIR}/utils/ms_extra_utils.c\
		${SUBDIR}/utils/ms_memory_utils.c\
		${SUBDIR}/utils/ms_signal_utils.c\
		${SUBDIR}/utils/ms_readline_utils.c\

OBJ		= $(patsubst ${SUBDIR}/%.c, ${OBJDIR}/%.o, ${SRCS})

NAME	= minishell

CFLAGS	= -Wall -Werror -Wextra -O2

LFLAGS = -Llibft -lft -lreadline

CC = cc

${NAME}:	${OBJ}
			make -C libft all
			${CC} ${OBJ} -o ${NAME} ${LFLAGS}

${OBJDIR}/%.o:	${SUBDIR}/%.c | ${OBJDIR}
				${CC} ${CFLAGS} -c $< -o $@

${OBJDIR}:
		mkdir -p $@
		mkdir -p ${OBJDIR}/exec
		mkdir -p ${OBJDIR}/piping
		mkdir -p ${OBJDIR}/parsing
		mkdir -p ${OBJDIR}/utils

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

re:		fclean
		${MAKE} all

.PHONY: all fclean clean re
