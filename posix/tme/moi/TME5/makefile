CFLAGS = -Wall -ansi
CC=gcc
LP=-lrt
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/


all: init ${BIN}exo1 ${BIN}exo2 ${BIN}exo3 ${BIN}exo4 ${BIN}exo5 ${BIN}exo6


init: 
	mkdir ${BIN}
	mkdir ${OBJ}

exo1: ${BIN}exo1
	./$<

exo2: ${BIN}exo2
	./$< 

client: ${BIN}client
	./$<

serveur: ${BIN}serveur
	./$< test

exo4: ${BIN}exo4
	./$<


${BIN}exo1: ${SRC}exo1.c
	${CC} ${CFLAGS} ${LP} $< -o $@

${BIN}exo2: ${SRC}exo2.c
	${CC} ${CFLAGS} ${LP} $< -o $@

${BIN}client: ${SRC}client.c
	${CC} ${CFLAGS} ${LP} $< -o $@

${BIN}serveur: ${SRC}serveur.c
	${CC} ${CFLAGS} ${LP} $< -o $@

${BIN}exo4: ${SRC}exo4.c
	${CC} ${CFLAGS} $< -o $@


${OBJ}thread_stack_shm.o: ${SRC}thread_stack_shm.c  ${INC}thread_stack_shm.h
	${CC} ${CFLAGS} -c $< -o ${OBJ}thread_stack_shm.o
