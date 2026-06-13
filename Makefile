CC = gcc
CFLAGS = -Wall -Wextra -g


TARGET = editor
SRCS = $(wildcard main.c src/*.c src/**/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY: all clean run debug valgrind
