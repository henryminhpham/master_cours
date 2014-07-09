CFLAGS = -Wall -ansi
CC=gcc
LP=-lrt
SRC=src/
OBJ=obj/
BIN=bin/
INC=include/


all: init ${BIN}exo1 ${BIN}recvfile ${BIN}sendfile ${BIN}serv_ftp ${BIN}cli_ftp ${BIN}client_env ${BIN}server_env


init: 
	mkdir ${BIN}
	mkdir ${OBJ}

exo1: ${BIN}exo1
	./$<

recvfile: ${BIN}recvfile
	./$< 33333

sendfile: ${BIN}sendfile
	./$< 0.0.0.0 33333 fich1

serv_ftp: ${BIN}serv_ftp
	./$< 10020

cli_ftp: ${BIN}cli_ftp
	./$< 0.0.0.0 10020

client_env: ${BIN}client_env
	./$<

server_env: ${BIN}server_env
	./$<



${BIN}exo1: ${SRC}exo1.c
	${CC} ${CFLAGS} $< -o $@

${BIN}recvfile: ${SRC}recvfile.c
	${CC} ${CFLAGS} $< -o $@

${BIN}serv_ftp: ${SRC}serv_ftp.c
	${CC} ${CFLAGS} $< -o $@

${BIN}sendfile: ${SRC}sendfile.c
	${CC} ${CFLAGS} $< -o $@

${BIN}cli_ftp: ${SRC}cli_ftp.c
	${CC} ${CFLAGS} $< -o $@

${BIN}client_env: ${SRC}client_env.c
	${CC} ${CFLAGS} $< -o $@

${BIN}server_env: ${SRC}server_env.c
	${CC} ${CFLAGS} $< -o $@
