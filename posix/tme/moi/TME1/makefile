CFLAGS = -Wall -ansi
CC=gcc
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/

all: init ${BIN}max_calcul ${BIN}exo2 ${BIN}exo3 ${BIN}exo4 ${BIN}exo5 ${BIN}exo6



init: 
	mkdir bin
	mkdir obj




max_calcul: ${BIN}max_calcul
	./$@ 4 8 12 7

exo2: ${BIN}exo2
	./$<

exo1: ${BIN}max_calcul
	./$<

exo3: ${BIN}exo3
	./$<

exo4: ${BIN}exo4
	./$<

exo5: ${BIN}exo5
	./$<

exo6: ${BIN}exo6
	./$<

exo7: ${BIN}exo7
	./$<




${BIN}max_calcul: ${OBJ}max_func.o ${SRC}max_calcul.c
	${CC} ${CFLAGS} $^ -o $@

${OBJ}max_func.o: ${SRC}max_func.c ${INC}max_func.h
	${CC} ${CLFAGS} -c $< -o $@

${BIN}exo2: ${OBJ}nfork.o ${SRC}exo2.c
	${CC} ${CLFAGS} $^ -o $@

${OBJ}nfork.o: ${SRC}nfork.c ${INC}nfork.h
	${CC} ${CFLAGS} -c $< -o $@ 

${BIN}exo3: ${SRC}exo3.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo4: ${SRC}exo4.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo5: ${SRC}exo5.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo6: ${SRC}exo6.c
	${CC} ${CFLAGS} $< -o $@

${BIN}exo7: ${SRC}exo7.c
	${CC} ${CFLAGS} $< -o $@




clean: 
	rm -rf ${OBJ}*