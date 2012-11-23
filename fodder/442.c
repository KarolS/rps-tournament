#include <stdio.h>
#include <stdlib.h>
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

#define PROGRAM_NAME "442 (Dumb)"

int* my_history;
int* opp_history;
int  turns_passed = 0;
int  game_length;

int get_next_move(){
	switch (rand() % 5) {
		case 0:
		case 1:
			return ROCK;
		case 2:
		case 3:
			return PAPER;
		default:
			return SCISSORS;
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