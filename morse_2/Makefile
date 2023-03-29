CC = gcc
CPPFLAGS =-MMD
CFLAGS = -Wall -Wextra -w -std=c99

SRC = trad_morse.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: trad_morse

trad_morse: ${OBJ}

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

#END