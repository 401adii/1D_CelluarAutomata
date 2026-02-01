CC = gcc

CFLAGS = -Wall -Wextra -Werror

TARGET = a.out

SOURCES = main.c Cell.c CellRow.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)
	./${TARGET}

clean:
	rm -f $(TARGET)
