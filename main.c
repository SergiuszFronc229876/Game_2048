#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "game.h"

#define ROWS 4
#define COLS 4

void draw_board(struct Game *game) {
    system("cls"); // Wyczyszczenie konsoli
    printf("Score: %d\n\n", game->score);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%-5d", game->board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    struct Game game = {0};
    spawn_number(&game);
    spawn_number(&game);
    draw_board(&game);
    while (1) {
        char ch = getch();
        switch (ch) {
            case 'w':
            case 'W':
                move_up(&game);
                break;
            case 's':
            case 'S':
                move_down(&game);
                break;
            case 'a':
            case 'A':
                move_left(&game);
                break;
            case 'd':
            case 'D':
                move_right(&game);
                break;
            case 'q':
            case 'Q':
                exit(0);
            default:
                continue;
        }
        spawn_number(&game);
        draw_board(&game);
    }
    return 0;
}