#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "game.h"

#define ROWS 4
#define COLS 4

void print_board(struct Game *game) {
    system("cls"); // Clear the console
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

    struct Game game;
    init_game(&game);

    while (1) {
        print_board(&game);
        if (game_over(&game)) {
            printf("Game over! Final score: %d\n", game.score);
            break;
        }
        int move = getch();
        int moved;
        switch (move) {
            case 'w':
                moved = move_up(&game);
                break;
            case 's':
                moved = move_down(&game);
                break;
            case 'a':
                moved = move_left(&game);
                break;
            case 'd':
                moved = move_right(&game);
                break;
            default:
                continue;
        }
        if (moved) {
            spawn_number(&game);
        }
    }
    return 0;
}