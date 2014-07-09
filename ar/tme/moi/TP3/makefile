CFLAGS = -Wall -ansi
CC=mpicc
LP=-lrt
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/
EXECUTER=mpirun
NBPROCS=7



all: init $(BIN)arbre $(BIN)echo 
	
init: 
	mkdir $(BIN)
	mkdir $(OBJ)


goarbre: $(BIN)arbre
	$(EXECUTER) -np $(NBPROCS) $<

goecho: $(BIN)echo
	$(EXECUTER) -np $(NBPROCS) $<


$(BIN)arbre: $(SRC)arbre_mpi.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN)echo: $(SRC)echo_mpi.c
	$(CC) $(CFLAGS) $< -o $@