#ifndef HEADER_H
#define HEADER_H

int checkWinner(char *board);
int isDraw(char *board);
int evaluate(char *board);
int minimax(char *board, int isMaximizing);
int findBestMove(char *board);

#endif