#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <thread>
#include <chrono>
using namespace std;


void check (int board[]  [7], int row, int col,  int& counter, int * prow, int * pcol, char look, int player) ;
bool checkWin (int board[] [7], int player);
void displayBoard(int board [] [7]);
void updateBoard(int board [] [7], int column, int player);
int comPick(int board [] [7]);
int check3(int board [] [7], int player);
int check2(int board [] [7], int player);

int main () {
    int numPlay;
    bool comPlayer;
    cout << "Welcome to the Game connect 4, please enter the number of players ( 1 or 2): "; cin >> numPlay;
    cout << "Okay Player one, your spots will be marked by an 'X'.\nPlayer 2,  will be marked as a 'O'\n\n\n" << endl;

    if (numPlay == 1)
        comPlayer = true;

    this_thread::sleep_for(chrono::seconds(2));
    //cout << "Ready to play? (y/n)."; cin >> numPlay;
    //initialize the board
    int gameBoard [6][7] = { \
    {0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0}  };
    bool winner=false;
    int turnCount = 0;
    int player;
    int pick;
    displayBoard(gameBoard);
    if (comPlayer) {
        while (!winner) {
            player = turnCount % 2 + 1;
            cout << "------------------------------------------------\n";
            cout << "turn " << turnCount << endl;
            cout << "player " << player << " pick a column to drop your token: ";
            if  (player == 1){
                cin >> pick; cout << "\n\n\n\n";
            }else if (player == 2)
                pick = comPick(gameBoard);
                cout << pick;
                cout << "\n\n\n\n";
            updateBoard(gameBoard, pick, player);
            displayBoard(gameBoard);
            winner = checkWin(gameBoard, player);
            turnCount++;

        }
    } else {
        while (!winner) {
            player = turnCount % 2 + 1;

            cout << "------------------------------------------------\n";
            cout << "turn " << turnCount << endl;
            cout << "player " << player << " pick a column to drop your token: ";
            cin >> pick; cout << "\n\n\n\n";

            updateBoard(gameBoard, pick, player);
            displayBoard(gameBoard);

            winner = checkWin(gameBoard, player);
            turnCount++;
            }

    }
    cout << "congrats player " << player << " you winnnn\n";
    return 0;
}

void updateBoard(int board [] [7], int column, int player){
    column--;
    if (board [0] [column]  != 0 )
        cout << "that column is full, you lose this turn\n";
    else{
        for (int i=5; i >=0; i--){
            if (board[i][column] == 0){
               // cout << board[i][column] <<  "before \n";
                board[i] [column] = player;
            //    cout<< board[i][column] << "after \n";
                break;
            }
        }
    }
}

void displayBoard(int board[] [7]){
    map <int, char> dimap = {{0, ' '}, {1, 'X'}, {2, '0'} };
    cout << "  1      2      3      4      5      6      7\n";
    for ( int i = 0; i < 6; i++) {
        cout << " ___    ___    ___    ___    ___    ___    ___\n";
		for (int j = 0; j < 7; j++) {
                cout << "| " << dimap.at(board[i] [j]) << " |  ";
		}
        cout << "\n ---    ---    ---    ---    ---    ---    ---\n";
    }
}

bool checkWin (int board[] [7], int player) {
	int directions [4] [2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

	for ( int i = 5; i  >=0; i--) {
		for (int j = 6; j >=0; j--) {
			if (board [i][j] == player) {
               // cout << i << j<< endl;
				for (int k=0; k < 4; k++){
                    int * prow = &directions[k] [0], *pcol = &directions[k] [1];
                    int counter = 1;
                    check(board, i, j, counter, prow, pcol, 'b', player);
                    check(board, i, j, counter, prow, pcol, 'f', player);
                    if (counter >= 4){
                        return true;
                    }
                }
			}
        }
	}
    return false;
}

void check (int board[]  [7], int row, int col,  int& counter, int * prow, int * pcol, char look, int player) {
	//define what direction to  shift
    int newRow;
    int newCol;
    newRow = (look == 'f') ? row + *prow : row - *prow;
    newCol = (look == 'f') ?  col + *pcol : col - *pcol;

    if ((newRow >= 0) && (newRow <= 5) && (newCol >= 0) && (newCol <= 6)) {
        if (board[newRow] [newCol] == player){
            counter++;
            check(board, newRow, newCol, counter, prow, pcol, look, player);
        }
    }
}

int check3(int board [] [7], int player){
    int directions [4] [2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    for ( int row= 5; row >=0; row--) {
		for (int col= 6; col >=0; col--) {
		   // cout << row << col <<board[row][col] << board[row-1][col] <<endl;
            if ((board[row][col] == 0) && (board[row+1][col] != 0)){
                for (int k=0; k < 4; k++){
                    int * prow = &directions[k] [0], *pcol = &directions[k] [1];
                    int counter = 0;

                    check(board, row, col, counter, prow, pcol, 'b', player);
                    check(board, row, col, counter, prow, pcol, 'f', player);
                    //cout << row << col <<counter<< endl;
                    if (counter == 3){
                        return ++col;
                    }
                }
            }
        }
    }
    return 0;
}

int check2(int board [] [7], int player){
    //for future implementation
    //return 0 for now
    return 0
}
int comPick(int board [] [7]){
    //first check to see if player 1 has a chance at winning
    if (check3(board, 1) > 0 ) {
        return check3(board, 1);
    }
    //try to connect 4
    if (check3(board, 2) > 0){
        return check3(board, 2);
    }
    //build to 3
    if (check2(board, 2>0) {
	return check2(board, 2);
    }
    //stop opponent from building to 3
    if (check2(board, 1){
        return check2(board, 1);
    }
    int col = rand() % 7 + 1;
    return col;
}

