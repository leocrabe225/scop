NAME = leo_scop
CC = g++
# -Wall -Werror -Wextra
CFLAGS =  -std=c++11
OPENGL = -lglfw3 -lGL -lX11
#OPENGL = -lglut -lGLU -lGL -lGLEW -lglfw  

SRCS =	main.cpp glad.c shader.cpp parser.cpp dotObj.cpp stb_image.cpp utils.cpp textureLoader.cpp texture.cpp window.cpp inputHandler.cpp vertexArrayObject.cpp Game.cpp VertexArrayObjectHandler.cpp ElementArrayBuffer.cpp

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