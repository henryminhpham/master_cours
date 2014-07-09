CC=gcc
# On ne met pas -ansi car certains commentaires peuvent faire planter la compilation (é, ', ... dans les commentaires)
CFLAGS=-Wall
# On lance toutes les directives pour tous les exercices
ALL=clean exo1 exo2 exo3 exo4 exo5 exo6
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

exo3:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@
	
exo4:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

exo5:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

exo6: exo6-stack
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} obj/$<.o -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@
	
exo6-stack:
	${CC} -o ${OBJ} -I include/ -c src/$@.c ${CFLAGS}
	
clean:
	@echo "Début du nettoyage..."
	rm -f bin/* obj/*.o lib/*.a
	@echo "Fin du nettoyage."
