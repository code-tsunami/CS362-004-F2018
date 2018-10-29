SHELL:=bash

EXEC = testme
SRC = $(EXEC).c
CC = gcc
ifeq ($(shell hostname),TheTsunami)
	CC = gcc-8
endif
CFLAGS = -Wall -pedantic
VGFLAGS = --leak-check=full --show-reachable=yes
FILES_TO_RM = $(shell find . -maxdepth 1 -type f ! -name "*.c" ! -name "Makefile")

default: $(EXEC)

${EXEC}: ${SRC}
	${CC} ${CFLAGS} ${SRC} -o ${EXEC}
	./${EXEC}

.PHONY: valgrind
valgrind:
	${CC} ${CFLAGS} -g ${SRC} -o ${EXEC}
	valgrind ${VGFLAGS} ${EXEC}

.PHONY: clean
clean:
	rm -f ${FILES_TO_RM}
