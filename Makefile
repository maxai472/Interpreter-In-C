CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra
TARGET  = clox

SRC = \
  main.c \
  chunk.c \
  memory.c \
  debug.c \
	value.c \
	vm.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
