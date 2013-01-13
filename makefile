LIBS = -lglut -lGL -lm -lGLU -lpthread

SRC=$(wildcard *.c)

	
all: $(SRC)
	clear
	gcc $^ $(LIBS) -o prog


run: all
	./prog
