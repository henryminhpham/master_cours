CFLAGS = -Wall -ansi
CC=mpicc
LP=-lrt
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/


all: init ${BIN}tp1_1 ${BIN}tp1_2 ${BIN}tp1_3 $(BIN)tp1_4

init: 
	mkdir $(OBJ)
	mkdir $(BIN)

clean: 
	rm -rf $(OBJ)*


tp1_1: ${BIN}tp1_1
	mpirun -np 5 $<

tp1_2: ${BIN}tp1_2
	mpirun -np 25 $<

tp1_3: ${BIN}tp1_3
	mpirun -np 12 $<


tp1_4: ${BIN}tp1_4
	mpirun -np 8 $<

${BIN}tp1_1: ${SRC}tp1_1.c
	${CC} $< -o $@

${BIN}tp1_2: ${SRC}tp1_2.c
	${CC} $< -o $@

${BIN}tp1_3: ${SRC}tp1_3.c
	${CC} $< -o $@

${BIN}tp1_4: ${SRC}tp1_4.c $(OBJ)server.o
	${CC} $^ -o $@

$(OBJ)server.o: $(SRC)server.c $(SRC)server.h
	$(CC) -c $(CFLAGS) ${SRC}server.c -o $@
