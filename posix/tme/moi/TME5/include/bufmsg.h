#ifndef __BUFMSG

#define __BUFMSG

typedef struct request {
	long type;/*0 : connexion, 1: diffusion de mesage, 2: Deconnexion*/
	char content[1024];
} request;

#endif