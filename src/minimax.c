#include "../include/header.h"

//1 if x won, -1 if o won, 0 if game still going
int checkWinner(char *board) {
    //row check
    if(board[0] == board[1] &&  board[1] == board[2]) {
        if(board[0] == 'x') return 1;
        else if(board[0] == 'o') return -1;
    }
    else if(board[3] == board[4] &&  board[4] == board[5]) {
        if(board[3] == 'x') return 1;
        else if(board[3] == 'o') return -1;
    }
    else if(board[6] == board[7] &&  board[7] == board[8]) {
        if(board[6] == 'x') return 1;
        else if(board[6] == 'o') return -1;
    }
    //column check
    else if(board[0] == board[3] &&  board[3] == board[6]) {
        if(board[0] == 'x') return 1;
        else if(board[0] == 'o') return -1;
    }
    else if(board[1] == board[4] &&  board[4] == board[7]) {
        if(board[1] == 'x') return 1;
        else if(board[1] == 'o') return -1;
    }
    else if(board[2] == board[5] &&  board[5] == board[8]) {
        if(board[2] == 'x') return 1;
        else if(board[2] == 'o') return -1;
    }
    //diagonal check
    else if(board[0] == board[4] &&  board[4] == board[8]) {
        if(board[0] == 'x') return 1;
        else if(board[0] == 'o') return -1;
    }
    else if(board[2] == board[4] &&  board[4] == board[6]) {
        if(board[2] == 'x') return 1;
        else if(board[2] == 'o') return -1;
    }
    return 0;
}

//1 if draw, 0 if not
int isDraw(char *board) {
    int empty = 0;
    for(int i = 0; i < 9; i++) {
        if(board[i] == ' ') {
            empty = 1;
            break;
        }
    }
    if(checkWinner(board) == 0 && !empty) return 1;
    return 0;
}

//10 if bot wins, -10 if human wins, 0 if draw, -1 if game in process
int evaluate(char *board) {
    int stat = checkWinner(board);

    if(stat == -1) return 10;
    else if(stat == 1) return -10;
    else if(stat == 0 && !isDraw(board)) return -1;
    return 0;
}

// is maximizing = 1 means computer's turn 
int minimax(char *board, int isMaximizing) {
    int result = evaluate(board);
    if(result != -1) return result;
    int humanScore = 10, botScore = -10, score;

    for(int i = 0; i < 9; i++) {
        if(board[i] == ' ') {
            if(isMaximizing == 1) {
                board[i] = 'o';
                score = minimax(board, !isMaximizing);
                if(score > botScore) botScore = score;
            }
            else {
                board[i] = 'x';
                score = minimax(board, !isMaximizing);
                if(score < humanScore) humanScore = score;
            }
            board[i] = ' ';
        }
    }

    if (isMaximizing)
        return botScore;
    else
        return humanScore;
}

int findBestMove(char *board) {
    int score, maxScore = -10, maxIdx = -1;

    for(int i = 0; i < 9; i++) {
        if(board[i] == ' ') {
            board[i] = 'o';
            score = minimax(board, 0);
            if(score > maxScore) {
                maxScore = score;
                maxIdx = i;
            }
            board[i] = ' ';
        }

    }
    return maxIdx;
}