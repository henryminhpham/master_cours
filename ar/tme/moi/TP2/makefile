CFLAGS = -Wall -ansi
CC=mpicc
LP=-lrt
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/
EXECUTER=mpirun
NBPROCS=10



all: $(BIN)ricard
	$(EXECUTER) -np $(NBPROCS) $<

init: 
	mkdir $(BIN)
	mkdir $(OBJ)

$(BIN)ricard: $(SRC)Ricard_Agr.c
	$(CC) $< -o $@