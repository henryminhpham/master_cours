CFLAGS = -Wall -ansi
CC=gcc
LT=-lpthread
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/


all: init 


init: 
	mkdir ${BIN}
	mkdir ${OBJ}





exo1: ${BIN}exo1
	./$< hello.txt wild.txt world.txt

exo2: ${BIN}exo2
	./$< hello.txt wild.txt world.txt bye.txt

exo3: ${BIN}exo3
	./$<

exo4: ${BIN}exo4
	./$<

exo5: ${BIN}exo5
	./$<




${BIN}exo1: ${SRC}exo1.c 
	${CC} ${CFLAGS} ${LT} $^ -o $@


${BIN}exo2: ${SRC}exo2.c
	${CC} ${CFLAGS} ${LT} $< -o $@

${BIN}exo3: ${SRC}exo3.c ${OBJ}thread_stack.o
	${CC} ${CFLAGS} $^ -o $@

${BIN}exo4: ${SRC}exo4.c ${OBJ}thread_stack.o
	${CC} ${CFLAGS} $^ -o $@

${BIN}exo5: ${SRC}exo5.c ${OBJ}thread_stack.o
	${CC} ${CFLAGS} $^ -o $@



${OBJ}thread_stack.o: ${SRC}thread_stack.c  ${INC}thread_stack.h
	${CC} ${CFLAGS} -c $< -o ${OBJ}thread_stack.o