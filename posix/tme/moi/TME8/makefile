CFLAGS = -Wall -ansi
CC=gcc
LP=-lpthread
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/


all: init ${BIN}serv_ftp_multi ${BIN}cli_ftp ${BIN}mychat ${BIN}sonar ${BIN}ponger ${BIN}connectclient ${BIN}connectserver

init: 
	mkdir ${BIN}

serv_ftp_multi: ${BIN}serv_ftp_multi
	./$< 10020

cli_ftp: ${BIN}cli_ftp
	./$< 0.0.0.0 10020




${BIN}serv_ftp_multi: ${SRC}serv_ftp_multi.c
	${CC} ${CFLAGS} $< -o $@ ${LP}

${BIN}cli_ftp: ${SRC}cli_ftp.c
	${CC} ${CFLAGS} $< -o $@

${BIN}mychat: ${SRC}mychat.c
	${CC} ${CFLAGS} $< -o $@

${BIN}sonar: ${SRC}sonar.c
	${CC} ${CFLAGS} $< -o $@ ${LP}

${BIN}ponger: ${SRC}ponger.c
	${CC} ${CFLAGS} $< -o $@

${BIN}connectclient: ${SRC}connectclient.c
	${CC} ${CFLAGS} $< -o $@

${BIN}connectserver: ${SRC}connectserver.c
	${CC} ${CFLAGS} $< -o $@

