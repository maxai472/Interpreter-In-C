CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -MMD -MP
TARGET  = clox

SRC = \
  main.c \
  chunk.c \
  memory.c \
  debug.c \
  value.c \
  vm.c \
  scanner.c \
  compiler.c \
	object.c  \
	table.c

OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)
