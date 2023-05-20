# Makefile for Final Project in ECE586 - Spring 2023
# Created by Alexander Maso
########################################################################


parse: parse.c 
	gcc -g -Wall parse.c -o parse

clean: 
	rm parse
