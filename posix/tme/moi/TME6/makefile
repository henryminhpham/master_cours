CFLAGS = -Wall -ansi
CC=gcc
LT=-lpthread
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/


all: init ${BIN}exo1 ${BIN}exo2 ${BIN}exo3 ${BIN}exo4 ${BIN}exo51 ${BIN}exo52 ${BIN}exo6 ${BIN}exo7 ${BIN}exo8


init: 
	mkdir ${BIN}

exo1: ${BIN}exo1
	./$<

exo2: ${BIN}exo2
	./$< fich1 fich2

exo3: ${BIN}exo3
	./$< fich1 fich2

exo4: ${BIN}exo4
	./$<

exo51: ${BIN}exo51
	./$< fic_exo5.txt

exo52: ${BIN}exo52
	./$< fic_exo5.txt

exo6: ${BIN}exo6
	./$< exo bin/

exo7: ${BIN}exo7
	./$< fich1

exo8: ${BIN}exo8
	./$< fich1


${BIN}exo1: ${SRC}exo1.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo2: ${SRC}exo2.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo3: ${SRC}exo3.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo4: ${SRC}exo4.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo51: ${SRC}exo51.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo52: ${SRC}exo52.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo6: ${SRC}exo6.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo7: ${SRC}exo7.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo8: ${SRC}exo8.c
	${CC} ${CFLAGS} $< -o $@


