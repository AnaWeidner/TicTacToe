
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


#define size 9

int whowon = 0;
int positiontomove = 0;
int opened = 0;
int minimaxcount = 0;
int alphabetacount = 0;

void draw(int board[9]) {
	printf(" %d | %d | %d\n", (board[0]), (board[1]), (board[2]));
	printf("---+---+---\n");
	printf(" %d | %d | %d\n", (board[3]), (board[4]), (board[5]));
	printf("---+---+---\n");
	printf(" %d | %d | %d\n", (board[6]), (board[7]), (board[8]));

}

int win(const int board[9], int player) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    int count = 0;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
           if(player == board[wins[i][2]])
                return 10;

           else return -10;


    }
    for (int j = 0; j < size; j++){
        if (board[j] != 0)
            count++;
    }
    if(count == size)
        return 0;
    else return -1;
}
int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

int min(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}

int minimax(int* board, int depth, int maximizingPlayer) {
    minimaxcount++;
	if(win(board, 1) == 10){
        return 10 - depth;
	}
    else if(win(board, -1) == 10){

        return depth -10;
    }
    else if(win(board, maximizingPlayer) == 0){
        return 0;
    }
	float bestValue;
	int val = 0;

	if (maximizingPlayer == 1) {

		bestValue = -INFINITY;
		for (int i = 0; i < 9; i++) {
			if (board[i] == 0) {
				board[i] = 1;
				val = minimax(board, depth + 1, maximizingPlayer * -1);

				if (val > bestValue) {
					bestValue = val;
					positiontomove = i;
				}

				board[i] = 0;
			}
		}
		return bestValue;
	}
	else if(maximizingPlayer == -1) {
		bestValue = INFINITY;
		for (int i = 0; i < 9; i++) {
			if (board[i] == 0) {
				board[i] = -1;
				val = minimax(board, depth + 1, maximizingPlayer * -1);
				if (val < bestValue) {
					bestValue = val;
					positiontomove = i;
				}
				board[i] = 0;
			}
		}
		return bestValue;
	}

}

int alphabeta(int* board, int depth,float a, float b, int maximizingPlayer) {
    alphabetacount++;
    if(win(board, 1) == 10){
        return 10 - depth;
	}
    else if(win(board, -1) == 10){
        return depth -10;
    }
    else if(win(board, maximizingPlayer) == 0){
        return 0;
    }

	int move = 0;
    int val = 0;
    float bestValue;
	if (maximizingPlayer) {
        bestValue = -INFINITY;
		for (int i = 0; i < 9; i++) {
			if (board[i] == 0) {
				board[i] = 1;
				val = alphabeta(board, depth + 1, a,b,maximizingPlayer * -1);
				if(val > bestValue){
                    bestValue = val;

				}
				if(bestValue > a){
                    a = bestValue;
                    positiontomove = i;
				}
				board[i] = 0;
				if (a >= b) {

					break;
				}
			}
		}
		return bestValue;
	}
	else if(maximizingPlayer == -1){
        bestValue = INFINITY;
		for (int i = 0; i < 9; i++) {

			if (board[i] == 0) {
				board[i] = -1;
				val = alphabeta(board, depth + 1,a,b, maximizingPlayer * -1);
				if(val < bestValue){
                    bestValue = val;

				}
				if(bestValue < b){
                    b = bestValue;
                    positiontomove = i;
				}
				board[i] = 0;
				if (a >= b) {
					break;
				}
			}
		}
		return bestValue;
	}
}


void computerturn(int* board, int type) {

	printf("Computer's Turn!\n\n");
	if( type == 1){
		minimax(board, 0, 1);

	}
	else
        alphabeta(board,0,-INFINITY,INFINITY, 1);


}


int playerturn(int* board) {
	int position = 0;
	printf("Where do you want to mark with a -1?\n");
	scanf("%d", &position);
	while (board[position] != 0) {
		printf("This space is already marked! Choose another:\n");
		scanf("%d", &position);
	}
	return position;
}

void initialize(int* board) {
	for (int i = 0; i < size; ++i) {
		board[i] = 0;
	}
}


int main() {
	int position = 0;
	int board[size];
	initialize(board);
	int turnNumber = 0;
	int turn =1;
	int type = 2;
	while(1){
	printf("1- Minimax or 2-AlphaBeta\n");
	scanf("%d", &type);

	initialize(board);
    draw(board);
    printf("\n");
	turnNumber = 0;
    turn = 1;
	while (turnNumber < size && win(board, 1) == -1) {
		if (turn == 1) {
                positiontomove = -1;
			if (win(board, 1) != -1 ){
				break;
			}
			else {

				computerturn(board, type);
				board[positiontomove] = 1;

			}
			draw(board);
			printf("\n");
			turn =2;
		}
		else {
            positiontomove = -1;
			if (win(board, 1) != -1) {
				break;
			}
			else {
				position = playerturn(board);
				board[position] = -1;
			}
			draw(board);
			printf("\n");
			turn = 1;
		}

		turnNumber++;
	}


	printf("alphabeta count %d\n", alphabetacount);
	printf("minimax count %d\n", minimaxcount);

	}
	return 0;
}

