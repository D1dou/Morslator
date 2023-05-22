CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -w -O3
TARGET = text_to_morse
SRC = text_to_morse.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
