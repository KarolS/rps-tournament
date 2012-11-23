/*
	The footer to put after entries from 1999
	See http://webdocs.cs.ualberta.ca/~darse/rsb-ts1.c
*/
int main(int argc, char** argv){
	int tmp;
	printf("%s\n", PROGRAM_NAME);
	fflush(stdout);
	scanf("%d", &tmp);
	srand(tmp);
	scanf("%d", &trials);
	my_history = malloc(sizeof(int)*(trials+1));
	opp_history = malloc(sizeof(int)*(trials+1));
	my_history[0] = 0;
	opp_history[0] = 0;
	while(1){
		tmp = get_next_move();
		printf("%d\n", tmp);
		my_history[0] ++;
		opp_history[0] ++;
		my_history[my_history[0]] = tmp;
		fflush(stdout);
		scanf("%d", opp_history+opp_history[0]);
	}
	return 0;
}