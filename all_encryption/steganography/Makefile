CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LIBS = -lm

all: test_encode test_encode_dummy

test_encode: test_encode.c encode.c decode.c types.h encode.h decode.h
	$(CC) $(CFLAGS) -o $@ test_encode.c encode.c decode.c $(LIBS)

test_encode_dummy: test_encode_dummy.c encode.c decode.c types.h encode.h decode.h
	$(CC) $(CFLAGS) -o $@ test_encode_dummy.c encode.c decode.c $(LIBS)

clean:
	rm -f test_encode test_encode_dummy

