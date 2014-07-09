************* README ********************

Compte rendu TME1 


Participant au TME : Kévin Gallardo



Liste des fichiers de l'archive : 

	src/ :  exo2.c		exo3.c		exo4.c		exo5.c		exo6.c		exo7.c		max_calcul.c	max_func.c	nfork.c
	include/ : max_func.h	nfork.h
	makefile
	README.txt



Utilisation : 
	
	Pour créer tous les fichiers executables, objets, ainsi que les reppertoires correspondants : > make
	Pour executer un des exercices : (exercice 1) > make max_calcul
									 (le reste) > make exo[No de l'exercice]
	Pour effacer les fichier objets : > make clean



Etat d'avancement :
	
	29/09 : tous fonctionnent sauf exercice 7
	30/09 : Exercice 7 résolu



Questions : 

	Exercice 2 : 
		9 processus sont créés.

		Arborescence :

+5754(i=1)
	|
	|
	|
+5755(i=2)
	|
	|
	|--------------------------------------------------|
+5756(i=3)                                         +5757(i=3)
	|                                                  |
	|                                                  |
	|----------|----------|                            |--------------|-------------|
  +5758      +5760      +5762                        +5759          +5761         +5763



  	Exercice 3 : 
  		2 processus sont créés.

 		Arborescence :

+P0 ("2 fils")
	  |
	  |
	  |
+P1 ("1 fils")
	  |
	  |
	  |
+P2 ("Sans fils")


		
		Lorsque l'on remplace le sleep de la libc par un execl(sleep), cela ne change pas le nombre de processus créés, par contre, lorsque l'on appelle execl, le code de notre programme initial est directement remplacé par celui du programme /bin/sleep, ce qui fait qu'après que le programme /bin/sleep ait terminé, nous ne revenons pas dans le main après l'appel de la fonction. Et étant donné que la fonction /bin/sleep de termine simplement après avoir effectué son opération, le processus se termine. Donc nous ne voyons pas s'afficher le phrase "Sans fils".
