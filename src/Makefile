CC=gcc
SDLFLAGS=`sdl-config --cflags --libs`
FLAGS=-Wextra -Wall -Werror -std=c99 -pedantic -g -ggdb3
CCFLAGS=$(CC) $(SDLFLAGS) $(FLAGS)
HEADER= game.h
SRC= map.c
OBJ= game.o

%.o : %.c
	$(CCFLAGS) -c $< -o $@
clean:
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	find . -name "*~" -delete
	find . -name "*#*" -delete
	find . -name "*core" -delete
	find . -name "*.log" -delete
	find . -name "a.out" -delete

distclean: clean
