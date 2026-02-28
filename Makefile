CC = gcc

CFLAGS = -g -O0 -Wall -Wextra -Werror -lncurses

LDLIBS = -lncurses

TARGET = automata

SOURCES = main.c Cell.c CellRow.c Rule.c CA.c UI.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET)
