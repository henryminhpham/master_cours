CFLAGS = -Wall -ansi
CC=gcc
LR=-lrt
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/


all: init ${BIN}exo1 


init: 
	mkdir ${BIN}
	mkdir ${OBJ}

exo1: ${BIN}exo1
	./$< fich1 "helloimkevinhowareyoubro qzkh hoy"

exo2: ${BIN}exo2
	./$< fich1 "helloimkevinhowareyoubro kdjhsk hey"

exo3: ${BIN}exo3
	./$< 

exo4: ${BIN}exo4
	./$< test

exo5: ${BIN}exo5
	./$<



${BIN}exo1: ${SRC}exo1.c
	${CC} ${CFLAGS} $< -o $@ ${LR}

${BIN}exo2: ${SRC}exo2.c
	${CC} ${CFLAGS} $< -o $@ ${LR}

${BIN}exo3: ${SRC}exo3.c
	${CC} ${CFLAGS} $< -o $@ ${LR}

${BIN}exo4: ${SRC}exo4.c
	${CC} ${CFLAGS} $< -o $@ ${LR}

${BIN}exo5: ${SRC}exo5.c
	${CC} ${CFLAGS} $< -o $@ ${LR}


