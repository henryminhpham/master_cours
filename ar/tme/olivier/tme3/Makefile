CC = mpicc
RUN = mpirun
CFLAGS = -Wall -Wextra
LDFLAGS =

SRC = src
OBJ = obj
LIB = lib
INC = include
BIN = bin
NAME=arbre_mpi
ECHO=echo

all: clean $(BIN)/$(NAME) $(BIN)/$(ECHO)

run: run1 run2

exercice1: $(BIN)/$(NAME)

exercice2 : $(BIN)/$(ECHO)

run1: $(BIN)/$(NAME)
	$(RUN) -np 7 $<
	
run2: $(BIN)/$(ECHO)
	$(RUN) -np 7 $<

$(BIN)/$(NAME): $(OBJ)/$(NAME).o | $(BIN)
	$(CC) $(CFLAGS) -o $@  $(OBJ)/$(NAME).o -I $(INC) $(LDFLAGS)

$(OBJ)/$(NAME).o: $(SRC)/$(NAME).c | $(OBJ)
	$(CC) -c $(CFLAGS) -o $@ $< -I $(INC) $(LDFLAGS)

$(BIN)/$(ECHO): $(OBJ)/$(ECHO).o | $(BIN)
	$(CC) $(CFLAGS) -o $@  $(OBJ)/$(ECHO).o -I $(INC) $(LDFLAGS)
	
$(OBJ)/$(ECHO).o: $(SRC)/$(ECHO).c | $(OBJ)
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