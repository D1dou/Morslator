CC = gcc
CPPFLAGS =-MMD
CFLAGS = -Wall -Wextra

SRC = analyse.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: analyse

analyse: ${OBJ}

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

#END