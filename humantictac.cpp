#include <iostream>
using namespace std;

char board[9]; 

void printBoard() {
    for (int i = 0; i < 3; i++) {
        cout << board[i*3] << '|' << board[i*3+1] << '|' << board[i*3+2] << endl;
        if (i < 2) cout << "-----" << endl;
    }
}

bool checkWinner(char player) {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, 
        {0,3,6}, {1,4,7}, {2,5,8}, 
        {0,4,8}, {2,4,6}           
    };
    for(int i=0; i<8; i++) {
        if (board[wins[i][0]] == player && board[wins[i][1]] == player && board[wins[i][2]] == player)
            return true;
    }
    return false;
}

bool checkDraw() {
    for (int i=0; i<9; i++) {
        if (board[i] == ' ') return false;
    }
    return true;
}

int main() {
    for(int i=0; i<9; i++) board[i] = ' ';

    cout << "Tic-Tac-Toe: Player X vs Player O" << endl;

    char currentPlayer = 'X';

    while (true) {
        printBoard();
        int move;
        cout << "Player " << currentPlayer << " move (0-8): ";
        cin >> move;

        if (move < 0 || move > 8 || board[move] != ' ') {
            cout << "Invalid move, try again." << endl;
            continue;
        }
        board[move] = currentPlayer;

        if (checkWinner(currentPlayer)) {
            printBoard();
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        } 

        if (checkDraw()) {
            printBoard();
            cout << "Draw!" << endl;
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}
