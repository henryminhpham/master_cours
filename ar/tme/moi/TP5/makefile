CFLAGS = -Wall -ansi
CC=mpicc
LP=-lrt
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/
EXECUTER=mpirun
NBPROCS=7



all: init $(BIN)phase
	
init: 
	mkdir $(BIN)
	mkdir $(OBJ)


gophase: $(BIN)phase
	$(EXECUTER) -np $(NBPROCS) $<


$(BIN)phase: $(SRC)phase.c
	$(CC) $(CFLAGS) $< -o $@
