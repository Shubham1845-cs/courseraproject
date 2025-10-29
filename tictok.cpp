#include <iostream>
#include <limits>
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

int minimax(bool isMaximizing) {
    if (checkWinner('O')) return 1;    
    if (checkWinner('X')) return -1;   
    if (checkDraw()) return 0;         
    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i=0; i<9; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimax(false);
                board[i] = ' ';
                if (score > bestScore) bestScore = score;
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i=0; i<9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimax(true);
                board[i] = ' ';
                if (score < bestScore) bestScore = score;
            }
        }
        return bestScore;
    }
}

void aiMove() {
    int bestScore = numeric_limits<int>::min();
    int move = -1;
    for (int i=0; i<9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(false);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    if (move != -1) board[move] = 'O';
}

int main() {
    for(int i=0; i<9; i++) board[i] = ' ';

    cout << "Tic-Tac-Toe: You (X) vs AI (O) using Minimax" << endl;

    while (true) {
        printBoard();
        int move;
        cout << "Your move (0-8): ";
        cin >> move;

        if (move < 0 || move > 8 || board[move] != ' ') {
            cout << "Invalid move, try again." << endl;
            continue;
        }
        board[move] = 'X';

        if (checkWinner('X')) {
            printBoard();
            cout << "You win!" << endl;
            break;
        }

        if (checkDraw()) {
            printBoard();
            cout << "Draw!" << endl;
            break;
        }

        aiMove();

        if (checkWinner('O')) {
            printBoard();
            cout << "AI wins!" << endl;
            break;
        }

        if (checkDraw()) {
            printBoard();
            cout << "Draw!" << endl;
            break;
        }
    }

    return 0;
}
