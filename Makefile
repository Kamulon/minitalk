SERVER 				= server
CLIENT 				= client
SERVER_B 			= server_bonus
CLIENT_B 			= client_bonus
HEADER				= minitalk.h

SRCS_SERVER 		= server.c 			utils.c
SRCS_CLIENT 		= client.c 			utils.c
SRCS_SERVER_B		= server_bonus.c	utils.c
SRCS_CLIENT_B		= client_bonus.c	utils.c

SERVER_OBJS			= ${SRCS_SERVER:%.c=%.o}
CLIENT_OBJS			= ${SRCS_CLIENT:%.c=%.o}
SERVER_OBJS_B		= ${SRCS_SERVER_B:%.c=%.o}
CLIENT_OBJS_B		= ${SRCS_CLIENT_B:%.c=%.o}

CC					= gcc
FLAGS 				= -Wall -Wextra -Werror

all			:	${SERVER} ${CLIENT}

bonus		:
				@make SERVER="${SERVER_B}"		\
				CLIENT="${CLIENT_B}"			\
				SERVER_OBJS="${SERVER_OBJS_B}"	\
				CLIENT_OBJS="${CLIENT_OBJS_B}"	\
				all

%.o 		:	%.c ${HEADER}
				$(CC) ${FLAGS} -I ${HEADER} -c $< -o $@

${SERVER}	:	${SERVER_OBJS} ${HEADER}
				$(CC) ${FLAGS} ${SERVER_OBJS} -o ${SERVER}

${CLIENT}	:	${CLIENT_OBJS} ${HEADER}
				$(CC) ${FLAGS} ${CLIENT_OBJS} -o ${CLIENT}

clean		:
				rm -f ${SERVER_OBJS} ${SERVER_OBJS_B} ${CLIENT_OBJS} ${CLIENT_OBJS_B}

fclean		: 	clean
				rm -f ${SERVER} ${SERVER_B} ${CLIENT} ${CLIENT_B}

re			:	fclean all

bre			:	fclean bonus

.PHONY		:	all bonus clean fclean re bre