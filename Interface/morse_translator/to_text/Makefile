CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -w -O3
TARGET = morse_translator
SRC = morse_translator.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

