#include <iostream>
#include <cstdlib>
#include <vector>
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
using namespace std;

#define PROGRAM_NAME "Sample Random C++"

vector<int> my_history;
vector<int> opp_history;
int  game_length;

int get_next_move(){
	// do your fancy maths here
	return rand()%3;
}

int main(int argc, char** argv){
	int tmp;
	cout << PROGRAM_NAME << endl;
	cin >> tmp;
	srand(tmp);
	cin >> game_length;
	while(1){
		tmp = get_next_move();
		cout << tmp << endl;
		my_history.push_back(tmp);
		cin >> tmp;
		opp_history.push_back(tmp);
	}
	return 0;
}