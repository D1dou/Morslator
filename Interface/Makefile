# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -std=c99 -w -O3
LDLIBS = `pkg-config --libs gtk+-3.0`

EXE = interface 

all: $(EXE)

$(foreach f, $(EXE), $(eval $(f):))

.PHONY: clean

clean:
	${RM} $(EXE)

# END
