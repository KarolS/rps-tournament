#include <stdio.h>
#include <stdlib.h>
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

#define PROGRAM_NAME "Gambitter (Dumb)"

int* my_history;
int* opp_history;
int  turns_passed = 0;
int  game_length;
int gambit = 0;

int get_next_move(){
	if(0 == turns_passed % 3){
		gambit = rand() & 7;
	}
	int th=10*gambit+turns_passed % 3;
	switch(th) {
		case 0:
		case 1: 
		case 2:
		case 22:
		case 30:
		case 40:
			return ROCK;
		case 21:
		case 31:
		case 51:
		case 52:
		case 61:
		case 70:
		case 71:
		case 72:
			return SCISSORS;
		default:
			return PAPER;
	}

}

int main(int argc, char** argv){
	int tmp;
	printf("%s\n", PROGRAM_NAME);
	fflush(stdout);
	scanf("%d", &tmp);
	srand(tmp);
	scanf("%d", &game_length);
	my_history = malloc(sizeof(int)*game_length);
	opp_history = malloc(sizeof(int)*game_length);
	while(1){
		tmp = get_next_move();
		printf("%d\n", tmp);
		my_history[turns_passed] = tmp;
		fflush(stdout);
		scanf("%d", opp_history+turns_passed);
		turns_passed ++;
	}
	return 0;
}