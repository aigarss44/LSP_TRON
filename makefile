LIBS = -lglut -lGL -lm

SRC=$(wildcard *.c)

all: $(SRC)
	clear
	gcc $^ $(LIBS) -o prog

run: all
	./prog
