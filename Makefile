CC = gcc

CFLAGS = -Wall -Wextra

TARGET = a.out

all:
	$(CC) $(CFLAGS) c_ca_test.c -o $(TARGET)
	./${TARGET}

clean:
	rm -f $(TARGET)
