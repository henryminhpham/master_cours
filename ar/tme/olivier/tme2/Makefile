CC = mpicc
RUN = mpirun
CFLAGS = -Wall -Wextra
LDFLAGS = -lpthread

SRC = src
OBJ = obj
LIB = lib
INC = include
BIN = bin

all: $(BIN)/ricard_agrawala

run: $(BIN)/ricard_agrawala
	$(RUN) -np 5 $<

$(BIN)/ricard_agrawala: $(OBJ)/ricard_agrawala.o $(OBJ)/mpi_server.o | $(BIN)
	$(CC) $(CFLAGS) -o $@  $(OBJ)/ricard_agrawala.o $(OBJ)/mpi_server.o -I $(INC) $(LDFLAGS)

$(OBJ)/mpi_server.o: $(SRC)/mpi_server.c | $(OBJ)
	$(CC) -c $(CFLAGS) -o $@ $< -I $(INC) $(LDFLAGS)

$(OBJ)/ricard_agrawala.o: $(SRC)/ricard_agrawala.c | $(OBJ)
	$(CC) -c $(CFLAGS) -o $@ $< -I $(INC) $(LDFLAGS)

$(SRC) $(INC) $(LIB) $(OBJ) $(BIN):
	mkdir $@

README.txt:
	@echo "=========================================================" >> $@
	@echo "                  -- TME ?? AR --"                         >> $@
	@echo "=========================================================" >> $@
	@echo ""                                                          >> $@
	@echo "-- ---------------------- Etudiants ---------------------" >> $@
	@echo "-- NOM          : PITTON"                                  >> $@
	@echo "-- PRENOM       : Olivier"                                 >> $@
	@echo "-- NO ETUDIANT  : 2800439"                                 >> $@
	@echo ""                                                          >> $@
	@echo "-- NOM          : "                                        >> $@
	@echo "-- PRENOM       : "                                        >> $@
	@echo "-- NO ETUDIANT  : "                                        >> $@
	@echo "-- ------------------------------------------------------" >> $@
	@echo ""                                                          >> $@
	@echo "-- ----------------- Directives Makefile ----------------" >> $@
	@echo "-- make           : Construit tous les binaires des"       >> $@
	@echo "	              	  execices 1 a ??"                        >> $@
	@echo ""                                                          >> $@
	@echo "-- make exerciceX : Construit le binaire de "              >> $@
	@echo "                    l'exercice X."                         >> $@
	@echo ""                                                          >> $@
	@echo "-- make runX      : Execute le binaire de l'exerciceX"     >> $@
	@echo "                    avec des argument par defaut"          >> $@
	@echo ""                                                          >> $@
	@echo "-- make clean     : Detruit tous les fichiers objets "     >> $@
	@echo "                    ainsi que tous les executables "       >> $@
	@echo "-- ------------------------------------------------------" >> $@
	@echo ""                                                          >> $@
	@echo "-- --------------- Reponses aux questions ---------------" >> $@

env: $(SRC) $(INC) $(LIB) README.txt

clean:
	rm -rf $(BIN) $(OBJ)
	find . -name "*~" -exec rm {} \;

.PHONY: all clean