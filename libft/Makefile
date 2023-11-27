SUBDIR	= srcs

OBJDIR	= objs

SRCS	=	${SUBDIR}/ft_atoi.c\
			${SUBDIR}/ft_bzero.c\
			${SUBDIR}/ft_calloc.c\
			${SUBDIR}/ft_gnl.c\
			${SUBDIR}/ft_isalnum.c\
			${SUBDIR}/ft_isalpha.c\
			${SUBDIR}/ft_isascii.c\
			${SUBDIR}/ft_isdigit.c\
			${SUBDIR}/ft_isprint.c\
			${SUBDIR}/ft_itoa.c\
			${SUBDIR}/ft_lstadd_back.c\
			${SUBDIR}/ft_lstadd_front.c\
			${SUBDIR}/ft_lstclear.c\
			${SUBDIR}/ft_lstdelone.c\
			${SUBDIR}/ft_lstiter.c\
			${SUBDIR}/ft_lstlast.c\
			${SUBDIR}/ft_lstmap.c\
			${SUBDIR}/ft_lstnew.c\
			${SUBDIR}/ft_lstsize.c\
			${SUBDIR}/ft_memchr.c\
			${SUBDIR}/ft_memcmp.c\
			${SUBDIR}/ft_memcpy.c\
			${SUBDIR}/ft_memmove.c\
			${SUBDIR}/ft_memset.c\
			${SUBDIR}/ft_printf.c\
			${SUBDIR}/ft_putchar_fd.c\
			${SUBDIR}/ft_putendl_fd.c\
			${SUBDIR}/ft_putnbr_fd.c\
			${SUBDIR}/ft_putstr_fd.c\
			${SUBDIR}/ft_split.c\
			${SUBDIR}/ft_strchr.c\
			${SUBDIR}/ft_strdup.c\
			${SUBDIR}/ft_striteri.c\
			${SUBDIR}/ft_strjoin.c\
			${SUBDIR}/ft_strlcat.c\
			${SUBDIR}/ft_strlcpy.c\
			${SUBDIR}/ft_strlen.c\
			${SUBDIR}/ft_strmapi.c\
			${SUBDIR}/ft_strncmp.c\
			${SUBDIR}/ft_strnstr.c\
			${SUBDIR}/ft_strrchr.c\
			${SUBDIR}/ft_strtrim.c\
			${SUBDIR}/ft_substr.c\
			${SUBDIR}/ft_tolower.c\
			${SUBDIR}/ft_toupper.c\

OBJ		= $(patsubst ${SUBDIR}/%.c, ${OBJDIR}/%.o, ${SRCS})

NAME	= libft.a

CFLAGS	= -Wall -Werror -Wextra -O2

CC = cc

${NAME}:	${OBJ}
			ar rc ${NAME} ${OBJ}

${OBJDIR}/%.o:	${SUBDIR}/%.c | ${OBJDIR}
				${CC} ${CFLAGS} -c $< -o $@

${OBJDIR}:
		mkdir -p $@

norminette:
		@norminette ./ > /dev/null && echo "Norminette OK!"

all:	${NAME}

clean:
		rm -rf ${OBJDIR}

fclean:	clean
		rm -f ${NAME}

re:		fclean
		${MAKE} all

.PHONY: all fclean clean re
