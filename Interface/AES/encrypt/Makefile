CC = gcc
CFLAGS = -Wall -Wextra -O2 -w
LIBS = -lcrypto
TARGET = encrypt_aes
SRC = encrypt_aes.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)
