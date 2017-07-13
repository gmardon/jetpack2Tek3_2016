NAME_SERVER			=		serverJ2T3

NAME_CLIENT			=		clientJ2T3

SRC_COMMON			= 		src/my_malloc.c			\
							src/my_error.c			\
							src/my_select.c			\
							src/get_next_line.c		\
							src/socket_utils.c

SRC_SERVER			=		src/server/main.c		\
							$(SRC_COMMON)

SRC_CLINT			=		src/client/instructions.c \
							src/client/main.c		  \
							$(SRC_COMMON)

OBJ_SERVER			=		$(SRC_SERVER:.c=.o)

OBJ_CLIENT			=		$(SRC_CLIENT:.c=.o)

CFLAGS			=		-W -Wall -Wextra -g -I./include/ -g

all:			zappy_ai zappy_server

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