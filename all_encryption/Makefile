CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
LIBS=-lm

all: main

main: main.o aes_decrypt.o blowfish.o rsa
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

aes_decrypt.o: aes_decrypt.c
	$(CC) $(CFLAGS) -c $<

blowfish.o: blowfish.c
	$(CC) $(CFLAGS) -c $<

rsa:
	$(CC) -I../include RSA.c -L . -lcrypto -lssl

clean:
	rm -f *.o main

