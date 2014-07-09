************* README ********************

Compte rendu TME7


Participant au TME : Kévin Gallardo



Liste des fichiers de l'archive : 

	src/ :	cli_ftp.c	client_env.c	exo1.c		recvfile.c	sendfile.c	serv_ftp.c	server_env.c
	makefile
	fich1
	README.txt



Utilisation : 
	
	Pour créer tous les fichiers executables, objets, ainsi que les reppertoires correspondants : > make

	Remarque : 
	-Des commandes de "simulation" sont mises à disposition, pour les éxécuter il suffit d'executer la commande make le permettant, ainsi il est possible de lancer un test avec des arguments pour le programme qui fonctionnent.
	Il faut cependant veiller à respecter l'ordre de lancement des clients et serveur correspondant à chacun exercice.
		Pour exercice 2 : d'abord 'make recvfile', puis sur un autre terminal 'make sendfile'
		Pour exercice 3 : d'abord 'make server_env' puis 'make client_env'
		Pour exercice 4 : 'make serv_ftp' puis 'make cli_ftp' 

	Concernant l'exercice 3 et 4 il est possible de fournir sequentiellement des commandes ce qui permet de ne pas avoir à relancer serveur ainsi que client à chaque fois que l'on veut effectuer une commande.

	Mise en place également d'une gestion d'erreur entre le serveur et le client, le serveur a la possibilité de retourner une erreur au client lorsqu'il en détécte une (un fichier qui veut être uploadé sur le serveur existe déjà etc..) qui permet une plus grande stabilité du programme. Utilisation de réponses du serveur avec un type = 5.

	Pour executer un des autres exercices : make exo{No de l'exercice}