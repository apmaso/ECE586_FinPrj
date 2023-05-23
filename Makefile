# Makefile for Final Project in ECE586 - Spring 2023
# Created by Alexander Maso
########################################################################


main: main.o 
	gcc -g -o main main.o -lm

main.o: main.c header.h
	gcc -g -c main.c 

clean: 
	rm main main.o
