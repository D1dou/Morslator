CC = gcc
CFLAGS = -Wall -Wextra -w
TARGET = decrypt_rsa
LIBS = -lcrypto

all: $(TARGET)

$(TARGET): decrypt_rsa.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGET)

