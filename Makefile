# Makefile for Final Project in ECE586 - Spring 2023
# Created by Alexander Maso
########################################################################


main: parse.o 
	gcc -g -o main parse.o -lm

parse.o: parse.c header.h
	gcc -g -c parse.c -lm

clean: 
	rm main parse.o
