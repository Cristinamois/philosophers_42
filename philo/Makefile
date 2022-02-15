NAME	=	philo



SRCS	=	doing_the_job.c init_all.c parsing.c \
			philo.c routine.c utils.c utils_part_two.c \
			check_on_philo.c

OBJS	=	${SRCS:.c=.o}


CC		=	cc
INCS	=	-I ./philo/
CFLAGS	=	-Wall -Wextra -Werror -pthread

-include $(DEPS)
all:		${NAME}
${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${INCS} $^ -o $@

.c.o:
			${CC} ${CFLAGS} ${INCS} -c $< -o $@


clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
