CC=gcc
# On ne met pas -ansi car certains commentaires peuvent faire planter la compilation (é, ', ... dans les commentaires)
CFLAGS=-Wall -lrt -pthread
# On lance toutes les directives pour tous les exercices
ALL=clean exo1 exo2 chat exo4
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

chat: chat_client chat_server

chat_server:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

chat_client:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@	

exo4:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@
	
clean:
	@echo "Début du nettoyage..."
	rm -f bin/* obj/*.o lib/*.a
	@echo "Fin du nettoyage."
