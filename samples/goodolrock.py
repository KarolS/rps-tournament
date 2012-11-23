#!/usr/bin/python
import random
import sys

PROGRAM_NAME = "Sample Ol' Rock Python"

MY_HISTORY = []
OPP_HISTORY = []
GAME_LENGTH = 0
ROCK = 0
PAPER = 1
SCISSORS = 2

def get_next_move():
	global MY_HISTORY, OPP_HISTORY, ROCK, PAPER, SCISSORS
	## do some fancy maths here
	return ROCK

def main():
	global MY_HISTORY, OPP_HISTORY, GAME_LENGTH, PROGRAM_NAME
	sys.stdout.write(PROGRAM_NAME+"\n")
	sys.stdout.flush()
	random.seed(int(raw_input()))
	GAME_LENGTH = int(raw_input())
	while True:
		my_move = get_next_move()
		sys.stdout.write(str(my_move)+"\n")
		sys.stdout.flush()
		opp_move = int(raw_input())
		MY_HISTORY.append(my_move)
		OPP_HISTORY.append(opp_move)

if __name__=="__main__": main()

