/*
	The header to put before entries from 1999
	See http://webdocs.cs.ualberta.ca/~darse/rsb-ts1.c
*/

#include <stdio.h>
#include <stdlib.h>
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define rock 0
#define paper 1
#define scissors 2
#define random() rand()

int* my_history;
int* opp_history;
int  turns_passed = 0;
int  trials;