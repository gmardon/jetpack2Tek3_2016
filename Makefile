NAME_SERVER			=		serverJ2T3

NAME_CLIENT			=		clientJ2T3

SRC_COMMON			= 		src/my_malloc.c			\
							src/my_error.c			\
							src/socket_utils.c		\
							src/utils.c

SRC_SERVER			=		src/server/main.c		\
							src/server/configuration.c \
							src/server/client.c		\
							src/server/server_socket.c \
							src/server/server.c		\
							src/server/client_list.c \
							src/server/client_handler.c \
							src/server/commands/id_cmd.c \
							src/server/commands/ready_cmd.c \
							$(SRC_COMMON)

SRC_CLIENT			=		src/client/window.c \
							$(SRC_COMMON)

OBJ_SERVER			=		$(SRC_SERVER:.c=.o)

OBJ_CLIENT			=		$(SRC_CLIENT:.c=.o)

CFLAGS			=		-W -Wall -Wextra -g -I./include/ -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

all:			clientJ2T3 serverJ2T3

serverJ2T3:			$(OBJ_SERVER)
				gcc -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS) -lm

clientJ2T3:			$(OBJ_CLIENT)
				gcc -o $(NAME_CLIENT) $(OBJ_CLIENT) $(CFLAGS)

clean:
				rm -rf $(OBJ_SERVER)
				rm -rf $(OBJ_CLIENT)

fclean:			clean
				rm -rf $(NAME_SERVER)
				rm -rf $(NAME_CLIENT)

re:			fclean all
