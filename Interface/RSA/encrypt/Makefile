CC = gcc
CFLAGS = -Wall -Wextra -w
TARGET = encrypt_rsa
LIBS = -lcrypto

all: $(TARGET)

$(TARGET): encrypt_rsa.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGET)

