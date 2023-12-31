GCC_OPTIONS=-Wall -pedantic 

INC = -I/opt/homebrew/Cellar/glfw/3.3.8/include/ -I ./
LIB = /opt/homebrew/Cellar/glfw/3.3.8/lib/

GL_OPTIONS=$(INC) -L$(LIB) -lglfw -framework OpenGL
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)

prog: InitShader.o example1.cpp
	g++ ./example1.cpp InitShader.o $(OPTIONS) -o $@  

InitShader.o:
	g++ $(GCC_OPTIONS) $(INC) -c ../comm/InitShader.cpp 

.PHONY: clean
clean:
	rm -f prog
	rm -f *.o

