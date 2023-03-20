#include <stdlib.h>
#include "game.h"

void spawn_number(struct Game *game) {
    int x, y;
    do {
        x = rand() % ROWS;
        y = rand() % COLS;
    } while (game->board[x][y] != 0);
    game->board[x][y] = (rand() % 2 + 1) * 2;
}

void move_up(struct Game *game) {
    for (int j = 0; j < COLS; j++) {
        for (int i = 1; i < ROWS; i++) {
            if (game->board[i][j] != 0) {
                int k = i;
                while (k > 0 && game->board[k - 1][j] == 0) {
                    game->board[k - 1][j] = game->board[k][j];
                    game->board[k][j] = 0;
                    k--;
                }
                if (k > 0 && game->board[k - 1][j] == game->board[k][j]) {
                    game->board[k - 1][j] *= 2;
                    game->board[k][j] = 0;
                    game->score += game->board[k - 1][j];
                }
            }
        }
    }
}

void move_down(struct Game *game) {
    for (int j = 0; j < COLS; j++) {
        for (int i = ROWS - 2; i >= 0; i--) {
            if (game->board[i][j] != 0) {
                int k = i;
                while (k < ROWS - 1 && game->board[k + 1][j] == 0) {
                    game->board[k + 1][j] = game->board[k][j];
                    game->board[k][j] = 0;
                    k++;
                }
                if (k < ROWS - 1 && game->board[k + 1][j] == game->board[k][j]) {
                    game->board[k + 1][j] *= 2;
                    game->board[k][j] = 0;
                    game->score += game->board[k + 1][j];
                }
            }
        }
    }
}

void move_left(struct Game *game) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 1; j < COLS; j++) {
            if (game->board[i][j] != 0) {
                int k = j;
                while (k > 0 && game->board[i][k - 1] == 0) {
                    game->board[i][k - 1] = game->board[i][k];
                    game->board[i][k] = 0;
                    k--;
                }
                if (k > 0 && game->board[i][k - 1] == game->board[i][k]) {
                    game->board[i][k - 1] *= 2;
                    game->board[i][k] = 0;
                    game->score += game->board[i][k - 1];
                }
            }
        }
    }
}

void move_right(struct Game *game) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = COLS - 2; j >= 0; j--) {
            if (game->board[i][j] != 0) {
                int k = j;
                while (k < COLS - 1 && game->board[i][k + 1] == 0) {
                    game->board[i][k + 1] = game->board[i][k];
                    game->board[i][k] = 0;
                    k++;
                }
                if (k < COLS - 1 && game->board[i][k + 1] == game->board[i][k]) {
                    game->board[i][k + 1] *= 2;
                    game->board[i][k] = 0;
                    game->score += game->board[i][k + 1];
                }
            }
        }
    }
}