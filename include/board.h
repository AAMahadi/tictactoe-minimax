#ifndef BOARD_H
#define BOARD_H

#include <raylib.h>

extern Color bgColor;
extern Color boardColor;
extern Color gridColor;
extern Color xColor;
extern Color oColor;
extern Color winLineColor;

void drawBoard(char *board, int finished);
Rectangle getBoardHolder();


#endif