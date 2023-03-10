CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
LIBS=-lm

all: main

main: main.o aes_decrypt.o blowfish.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

aes_decrypt.o: aes_decrypt.c
	$(CC) $(CFLAGS) -c $<

blowfish.o: blowfish.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main

