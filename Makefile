# Makefile for Columnar Transposition Cipher
CC = gcc
CFLAGS = -Wall -Wextra -g

all: cipher

cipher: main.o functions.o
	  -o cipher main.o functions.o

main.o: main.c functions.h
	  -c main.c

functions.o: functions.c functions.h
	  -c functions.c

clean:
	rm -f *.o cipher
