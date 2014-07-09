CFLAGS = -Wall -ansi
CC=gcc
LT=-lpthread
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

exo3: ${BIN}exo3
	./$<

exo4: ${BIN}exo4
	./$<

exo6: ${BIN}exo6 
	./$<

exo5: ${BIN}exo5
	./$<


${BIN}exo1: ${SRC}exo1.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo2: ${SRC}exo2.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo3: ${SRC}exo3.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo4: ${SRC}exo4.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo6: ${SRC}exo6.c ${OBJ}thread_stack_shm.o
	${CC} ${CFLAGS} ${LT} $^ -o $@

${BIN}exo5: ${SRC}exo5.c
	${CC} ${CFLAGS} ${LT} $< -o $@


${OBJ}thread_stack_shm.o: ${SRC}thread_stack_shm.c  ${INC}thread_stack_shm.h
	${CC} ${CFLAGS} -c $< -o ${OBJ}thread_stack_shm.o
