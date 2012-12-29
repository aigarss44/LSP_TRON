LIBS = -lglut -lGL -lm -lGLU

SRC=$(wildcard *.c)

	
all: $(SRC)
	gcc $^ $(LIBS) -o prog


run: all
	./prog