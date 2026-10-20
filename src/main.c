#include "../include/board.h"
#include "../include/header.h"

int main() {
    const int screenWidth = 500;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "TIC-TAC-TOE MINIMAX");

    char board[9] = {' ', ' ', ' ',
                    ' ', ' ', ' ',
                    ' ', ' ', ' '};


    bool isBotsTurn = true;
    float timer = 0;
    
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        timer += GetFrameTime();

        Vector2 mousePos = GetMousePosition();
        if(!isBotsTurn && checkWinner(board) == 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, getBoardHolder())) {
            int row = (mousePos.y - getBoardHolder().y) / (getBoardHolder().height / 3);
            int col = (mousePos.x - getBoardHolder().x) / (getBoardHolder().width / 3);

            int idx = col + row * 3;

            if(board[idx] == ' ') board[idx] = 'x';
            else continue;

            isBotsTurn = true;
            timer = 0;
        }
        if(timer >= 1 && isBotsTurn) {
            int move = findBestMove(board);
            if(move != -1) board[move] = 'o';
            isBotsTurn = false;
        }
        if((checkWinner(board) != 0 || isDraw(board)) && IsKeyPressed(KEY_R)) {
            for(int i = 0; i < 9; i++) {
                board[i] = ' ';
            }
            isBotsTurn = true;
            timer = 0;
        }
        int finished = (checkWinner(board) == 0)? 0:1;
        BeginDrawing();
            ClearBackground(bgColor);

            //drawing the board
            drawBoard(board, finished);

            if(isDraw(board)) {
                DrawText("DRAW MATCH", (GetScreenWidth() - 200)/2, 50, 30, WHITE);
                DrawText("Press R to Restart", (GetScreenWidth() - 280)/2, 150, 30, WHITE);
            } 
            else if(checkWinner(board) == 1) {
                DrawText("You Won", (GetScreenWidth() - 130)/2, 50, 30, WHITE);
                DrawText("Press R to Restart", (GetScreenWidth() - 280)/2, 130, 30, WHITE);
            }
            else if(checkWinner(board) == -1) {
                DrawText("Bot Won", (GetScreenWidth() - 130)/2, 50, 30, WHITE);
                DrawText("Press R to Restart", (GetScreenWidth() - 280)/2, 130, 30, WHITE);
            }
            else if(isBotsTurn) {
                DrawText("Bot's Turn", (GetScreenWidth() - 180)/2, 100, 30, WHITE);
            }
            else if(!isBotsTurn){
                DrawText("Your Turn", (GetScreenWidth() - 180)/2, 100, 30, WHITE);
            }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}