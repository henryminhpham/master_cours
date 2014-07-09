CC=gcc
# On ne met pas -ansi car certains commentaires peuvent faire planter la compilation (é, ', ... dans les commentaires)
CFLAGS=-Wall -pthread
# On lance toutes les directives pour tous les exercices
ALL=clean ftpclient ftpserver mychat ponger sonar connectclient connectserver
OBJ=obj/$@.o

all : ${ALL}

ftpclient:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

ftpserver:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

mychat:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@
	
ponger: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ}  -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

sonar: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@

connectclient: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@
	
connectserver: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	@echo "Fin de la génération de" $@
	
clean: 
	@echo "Début du nettoyage..."
	rm -f bin/* obj/*.o lib/*.a
	@echo "Fin du nettoyage."
