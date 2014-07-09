CC=gcc
# On ne met pas -ansi car certains commentaires peuvent faire planter la compilation (é, ', ... dans les commentaires)
CFLAGS=-Wall -pthread
# On lance toutes les directives pour tous les exercices
ALL=clean exo1 exo2 exo3 exo4 exo5
OBJ=obj/$@.o

all : ${ALL}

exo1:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

exo2:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

exo3:thread_stack-1
	@echo "Génération de" $@ "en cours..."
	${CC} -o $(OBJ) -I include/ obj/$<.o src/$@.c $(CFLAGS)
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

thread_stack-1: 
	${CC} -o obj/$@.o -c src/thread_stack-1.c -I include/ ${CFLAGS}
	
exo4:thread_stack-1
	@echo "Génération de" $@ "en cours..."
	${CC} -o $(OBJ) -I include/ obj/$<.o src/$@.c $(CFLAGS)
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@
	
exo5:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

clean:
	@echo "Début du nettoyage..."
	rm -f bin/* obj/*.o lib/*.a
	@echo "Fin du nettoyage."
