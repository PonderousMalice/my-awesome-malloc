CC=gcc
CFLAGS=-Wextra -Werror -Wall -std=c99 -pedantic

INCLUDE=./include
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
LIB=libmalloc.so

.PHONY: all check clean debug

all: $(OBJ)
	$(CC) -shared $(OBJ) -o $(LIB)

clean:
	$(RM) $(OBJ) $(LIB)

check: all
	./tests/test.sh

debug: CFLAGS+= -g
debug: all

$(OBJ): CFLAGS+= -I $(INCLUDE) -fPIC
$(OBJ): $(SRC)
