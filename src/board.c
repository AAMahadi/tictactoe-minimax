#include "../include/board.h"

Color bgColor = {17, 19, 29, 255};  // #11131D
Color boardColor   = {30, 30, 46, 255};  // #1E1E2E
Color gridColor = {58, 63, 81, 255};  // #3A3F51
Color xColor   = {79, 195, 247, 255}; // #4FC3F7
Color oColor   = {255, 183, 77, 255}; // #FFB74D
Color winLineColor = {255, 107, 107, 255};

void drawBoard(char *board, int finished) {
    DrawRectangleRounded((Rectangle){1, (GetScreenHeight() - 500), 498, 498}, 0.15, 18, boardColor);

    Rectangle boardHolder = {(GetScreenWidth() - 480)/2, (GetScreenHeight() - 500) + (497 - 480)/2, 480, 480};
    DrawRectangleRec(boardHolder, boardColor);

    DrawRectangleRoundedLinesEx((Rectangle){2, (GetScreenHeight() - 500), 497, 498}, 0.15, 18, 1, gridColor);

    DrawLineEx((Vector2){boardHolder.x, boardHolder.y + (boardHolder.height - 4)/3}, (Vector2){boardHolder.x + boardHolder.width, boardHolder.y + (boardHolder.height - 4)/3}, 4, gridColor);
    DrawLineEx((Vector2){boardHolder.x, boardHolder.y + (boardHolder.height - 4)*2/3}, (Vector2){boardHolder.x + boardHolder.width, boardHolder.y + (boardHolder.height - 4)*2/3}, 4, gridColor);
    DrawLineEx((Vector2){boardHolder.x + (boardHolder.width - 4)/3, boardHolder.y}, (Vector2){boardHolder.x + (boardHolder.width - 4)/3, boardHolder.y + boardHolder.height}, 4, gridColor);
    DrawLineEx((Vector2){boardHolder.x + (boardHolder.width - 4)*2/3, boardHolder.y}, (Vector2){boardHolder.x + (boardHolder.width - 4)*2/3, boardHolder.y + boardHolder.height}, 4, gridColor);


    float cellWidth = boardHolder.width / 3;
    float cellHeight = boardHolder.height / 3;

    for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
            int idx = x + y*3;
            
            float centerX = boardHolder.x + x * cellWidth + cellWidth / 2;
            float centerY = boardHolder.y + y * cellHeight + cellHeight / 2;
            if(board[idx] == 'x') {
                DrawLineEx((Vector2){centerX - 30, centerY - 30}, (Vector2){centerX + 30, centerY + 30}, 6, xColor);
                DrawLineEx((Vector2){centerX + 30, centerY - 30}, (Vector2){centerX - 30, centerY + 30}, 6, xColor);
            }
            else if(board[idx] == 'o') {
                DrawRing((Vector2){centerX, centerY}, 27, 33, 0, 360, 48, oColor);
            }
        }
    }
    
    if(finished == 1) {
        float startX, startY, endX, endY;
        //1st row
        if(board[0] == board[1] && board[1] == board[2] && board[0] != ' ') {
            startX = boardHolder.x; endX = boardHolder.x+boardHolder.width;
            startY = boardHolder.y + cellHeight / 2; endY = boardHolder.y + cellHeight / 2;
        }
        //1st column
        else if(board[0] == board[3] && board[3] == board[6] && board[0] != ' ') {
            startX = boardHolder.x + cellWidth / 2; endX = boardHolder.x + cellWidth / 2;
            startY = boardHolder.y; endY = boardHolder.y + boardHolder.width;
        }
        //main diagonal
        else if(board[0] == board[4] && board[4] == board[8] && board[0] != ' ') {
            startX = boardHolder.x + cellWidth / 2 - 30; endX = boardHolder.x + 2 * cellWidth + cellWidth / 2 + 30;
            startY = boardHolder.y + cellHeight / 2 - 30; endY = boardHolder.y + 2 * cellHeight + cellHeight / 2 + 30;
        }
        //2nd column
        else if(board[1] == board[4] && board[4] == board[7] && board[1] != ' ') {
            startX = boardHolder.x + 1 * cellWidth + cellWidth / 2; endX = boardHolder.x + 1 * cellWidth + cellWidth / 2;
            startY = boardHolder.y; endY = boardHolder.y + boardHolder.width;
        }
        //3rd column
        else if(board[1] == board[4] && board[4] == board[7] && board[1] != ' ') {
            startX = boardHolder.x + 2 * cellWidth + cellWidth / 2; endX = boardHolder.x + 2 * cellWidth + cellWidth / 2;
            startY = boardHolder.y; endY = boardHolder.y + boardHolder.width;
        }
        //secondary diagonal
        else if(board[2] == board[4] && board[4] == board[6] && board[2] != ' ') {
            startX = boardHolder.x + 2 * cellWidth + cellWidth / 2 + 30; endX = boardHolder.x + cellWidth / 2 - 30;
            startY = boardHolder.y + cellHeight / 2 - 30; endY = boardHolder.y +  2 * cellHeight + cellHeight / 2 + 30;
        }
        //2nd row
        if(board[3] == board[4] && board[4] == board[5] && board[3] != ' ') {
            startX = boardHolder.x; endX = boardHolder.x+boardHolder.width;
            startY = boardHolder.y + 1 * cellHeight + cellHeight / 2; endY = boardHolder.y + 1 * cellHeight + cellHeight / 2;
        }
        //3rd row
        if(board[6] == board[7] && board[7] == board[8] && board[6] != ' ') {
            startX = boardHolder.x; endX = boardHolder.x+boardHolder.width;
            startY = boardHolder.y + 2 * cellHeight + cellHeight / 2; endY = boardHolder.y + 2 * cellHeight + cellHeight / 2;
        }
        DrawLineEx((Vector2){startX, startY}, (Vector2){endX, endY}, 4, winLineColor);
    }
}

Rectangle getBoardHolder() {
    return (Rectangle){(GetScreenWidth() - 480)/2, (GetScreenHeight() - 500) + (497 - 480)/2, 480, 480};
}