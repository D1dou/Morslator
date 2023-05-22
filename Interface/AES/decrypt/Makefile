CC = gcc
CFLAGS = -Wall -Wextra -w -O2
LIBS = -lcrypto
TARGET = decrypt_aes
SRC = decrypt_aes.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

