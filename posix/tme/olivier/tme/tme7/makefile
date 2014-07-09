CC=gcc
# On ne met pas -ansi car certains commentaires peuvent faire planter la compilation (é, ', ... dans les commentaires)
CFLAGS=-g -Wall -pthread
# On lance toutes les directives pour tous les exercices
ALL=clean exo1 sendfile recvfile client-exo3 server-exo3 ftpclient ftpserver

OBJ=obj/$@.o

all : ${ALL}

exo1:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

sendfile:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

recvfile:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

client-exo3:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

server-exo3:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

ftpserver:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

ftpclient:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

clean: 
	@echo "Début du nettoyage..."
	rm -f bin/* obj/*.o lib/*.a
	@echo "Fin du nettoyage."
