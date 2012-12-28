LIBS = -lglut -lGL -lm

SRC=$(wildcard *.c)

	
all: $(SRC)
	gcc $^ $(LIBS) -o prog


run: all
	./prog