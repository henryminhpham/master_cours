CFLAGS = -Wall -ansi
CC=gcc
LT=-lpthread
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/


all: init ${BIN}exo1 ${BIN}exo2 ${BIN}exo3 ${BIN}exo41 ${BIN}exo42 ${BIN}exo5


init: 
	mkdir ${BIN}

exo1: ${BIN}exo1
	./$<

exo2: ${BIN}exo2
	./$<

exo3: ${BIN}exo3
	./$<

exo41: ${BIN}exo41
	./$<

exo42: ${BIN}exo42
	./$<

exo5: ${BIN}exo5
	./$<


${BIN}exo1: ${SRC}exo1.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo2: ${SRC}exo2.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo3: ${SRC}exo3.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo41: ${SRC}exo41.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo42: ${SRC}exo42.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo5: ${SRC}exo5.c
	${CC} ${CFLAGS} ${LT} $< -o $@
