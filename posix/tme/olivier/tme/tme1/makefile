CC=gcc
# On ne met pas -ansi car certains commentaires peuvent faire planter la compilation (é, ', ... dans les commentaires)
CFLAGS=-Wall
# On lance toutes les directives pour tous les exercices
ALL=clean max_calcul exo2 exo3-1 exo3-2 exo4-1 exo4-2 exo5 exo6 exo7
# On crée une bibliothèque statique pour l'exercice. Je ne sais pas si cela était nécessaire ou pas,
# mais dans la mesure où l'on a un répertoire "lib/" contenant les points *.a, cela m'a permis d'apprendre la 
# commande "ar"
LIB=ar rcs lib/lib$@.a -o
OBJ=obj/$@.o

all : ${ALL}

max_calcul: obj/max_func.o obj/max_calcul.o
	@echo "Génération de" $@ "en cours..."
	${CC} -o bin/$@ $^
	${LIB} $^
	@echo "Fin de la génération de" $@

obj/max_func.o: 
	${CC} -o $@ -c src/max_func.c -I include/ ${CFLAGS}
	ar rcs lib/libmax_func.a -o $@
	
obj/max_calcul.o: 
	${CC} -o $@ -c src/max_calcul.c -I include/ ${CFLAGS}

exo2:
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	${LIB} ${OBJ}
	@echo "Fin de la génération de" $@
	
exo3-1: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	${LIB} ${OBJ}
	@echo "Fin de la génération de" $@

	
exo3-2: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	${LIB} ${OBJ}
	@echo "Fin de la génération de" $@
	
exo4-1: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	${LIB} ${OBJ}
	@echo "Fin de la génération de" $@

exo4-2: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	${LIB} ${OBJ}
	@echo "Fin de la génération de" $@

exo5: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	${LIB} ${OBJ}
	@echo "Fin de la génération de" $@

exo6: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	${LIB} ${OBJ}
	@echo "Fin de la génération de" $@
	
exo7: 
	@echo "Génération de" $@ "en cours..."
	${CC} -o ${OBJ} -I include/ src/$@.c ${CFLAGS}
	cp ${OBJ} bin/$@
	${LIB} ${OBJ}
	@echo "Fin de la génération de" $@	
	
clean: 
	@echo "Début du nettoyage..."
	rm -f bin/* obj/*.o lib/*.a
	@echo "Fin du nettoyage."