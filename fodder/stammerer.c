
#include <stdio.h>
#include <stdlib.h>
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

#define PROGRAM_NAME "Stammerer (Dumb)"

int* my_history;
int* opp_history;
int  turns_passed = 0;
int  game_length;

int get_next_move(){
	if(turns_passed){
		if (turns_passed & 1) {
			return my_history[turns_passed - 1];
		} else {
			switch (10*opp_history[turns_passed - 1] + opp_history[turns_passed - 2]){
				case 00:
				case 01:
				case 10:
					return PAPER;
				case 11:
				case 12:
				case 21:
					return SCISSORS;
				default:
					return ROCK;
			}
		}
	} else {
		return rand() % 3;
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