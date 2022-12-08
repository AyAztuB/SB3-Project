DYNAMIC = libsb3_dev.so
STATIC = libsb3_dev.a
HDR = sb3_dev.h
SRC = $(wildcard sb3_dev*.c)
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -DSB3_DEV_CRASH_WHEN_ERROR -Wall -Wextra -Werror -fPIC -lm

all: install

dynamic: $(OBJ)
	$(CC) -shared -o $(DYNAMIC) $(OBJ)

static: $(OBJ)
	ar -rcs $(STATIC) $(OBJ)

test: static
	gcc main.c -L. -lsb3_dev -lm

install: dynamic
	cp $(DYNAMIC) /usr/lib/
	cp $(HDR) /usr/include/

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(DYNAMIC) $(STATIC) a.out copy.bmp



