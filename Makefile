NAME = leo_scop
CC = g++
# -Wall -Werror -Wextra
CFLAGS =  -std=c++11
OPENGL = -lglfw3 -lGL
#OPENGL = -lglut -lGLU -lGL -lGLEW -lglfw  

SRCS =	main.cpp glad.c

all: COMP

COMP: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -Llib -Iinclude $(OPENGL) -o $(NAME)



clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf sources/classes/*.o
	rm -rf sources/*.o


re: fclean all

.PHONY: all clean fclean re