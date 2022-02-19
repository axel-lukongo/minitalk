NAME = minitalk

SRCS_SERVER = server.c utils.c
SRCS_CLIENT = client.c utils.c

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

OBJS_SERVER = ${SRCS_SERVER:.c=.o}
OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}

SERVER = server
CLIENT = client

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT) $(UTILS)

$(SERVER): $(OBJS_SERVER)
		$(CC) -o $(SERVER) $(OBJS_SERVER)

$(CLIENT): $(OBJS_CLIENT)
		$(CC) -o $(CLIENT) $(OBJS_CLIENT)

clean:
	${RM} ${OBJS_CLIENT} ${OBJS_SERVER}

fclean: clean
	${RM} ${CLIENT} ${SERVER}

re: fclean all
.PHONY: all clean fclean re
