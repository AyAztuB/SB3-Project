DYNAMIC = libsb3.so
STATIC = libsb3.a
HDR = sb3.h
SRC = $(wildcard sb3*.c)
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC

all: install

dynamic: $(OBJ)
	$(CC) -shared -o $(DYNAMIC) $(OBJ)

dynamic_debug: OBJ_debug
	$(CC) -shared -o $(DYNAMIC) $(OBJ)

static: $(OBJ)
	ar -rcs $(STATIC) $(OBJ)

static_debug: OBJ_debug
	ar -rcs $(STATIC) $(OBJ)

test: static
	gcc main.c -L. -lsb3

test_debug: static_debug
	gcc main.c -L. -lsb3

install: dynamic
	cp $(DYNAMIC) /usr/lib/
	cp $(HDR) /usr/include/
	cp sb3.t /usr/share/man/man3/sb3.3
	gzip /usr/share/man/man3/sb3.3

install_debug: dynamic_debug
	cp $(DYNAMIC) /usr/lib/
	cp $(HDR) /usr/include/
	cp sb3.t /usr/share/man/man3/sb3.3
	gzip /usr/share/man/man3/sb3.3

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

OBJ_debug:
	$(CC) -DSB3_CRASH_WHEN_ERROR $(CFLAGS) -c -o sb3_bmp.o sb3_bmp.c
	$(CC) -DSB3_CRASH_WHEN_ERROR $(CFLAGS) -c -o sb3_utils.o sb3_utils.c

clean:
	$(RM) $(OBJ) $(DYNAMIC) $(STATIC) a.out copy.bmp



