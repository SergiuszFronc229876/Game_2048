#include <stdlib.h>
#include "game.h"

void init_game(struct Game *game) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            game->board[i][j] = 0;
        }
    }
    spawn_number(game);
    spawn_number(game);
    game->score = 0;
}

void spawn_number(struct Game *game) {
    int x, y;
    do {
        x = rand() % ROWS;
        y = rand() % COLS;
    } while (game->board[x][y] != 0);
    game->board[x][y] = (rand() % 2 + 1) * 2;
}

int move_up(struct Game *game) {
    int moved = 0;
    for (int j = 0; j < COLS; j++) {
        for (int i = 1; i < ROWS; i++) {
            if (game->board[i][j] != 0) {
                int k = i;
                while (k > 0 && game->board[k - 1][j] == 0) {
                    game->board[k - 1][j] = game->board[k][j];
                    game->board[k][j] = 0;
                    k--;
                    moved = 1;
                }
                if (k > 0 && game->board[k - 1][j] == game->board[k][j]) {
                    game->board[k - 1][j] *= 2;
                    game->board[k][j] = 0;
                    game->score += game->board[k - 1][j];
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

int move_down(struct Game *game) {
    int moved = 0;
    for (int j = 0; j < COLS; j++) {
        for (int i = ROWS - 2; i >= 0; i--) {
            if (game->board[i][j] != 0) {
                int k = i;
                while (k < ROWS - 1 && game->board[k + 1][j] == 0) {
                    game->board[k + 1][j] = game->board[k][j];
                    game->board[k][j] = 0;
                    k++;
                    moved = 1;
                }
                if (k < ROWS - 1 && game->board[k + 1][j] == game->board[k][j]) {
                    game->board[k + 1][j] *= 2;
                    game->board[k][j] = 0;
                    game->score += game->board[k + 1][j];
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

int move_left(struct Game *game) {
    int moved = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 1; j < COLS; j++) {
            if (game->board[i][j] != 0) {
                int k = j;
                while (k > 0 && game->board[i][k - 1] == 0) {
                    game->board[i][k - 1] = game->board[i][k];
                    game->board[i][k] = 0;
                    k--;
                    moved = 1;
                }
                if (k > 0 && game->board[i][k - 1] == game->board[i][k]) {
                    game->board[i][k - 1] *= 2;
                    game->board[i][k] = 0;
                    game->score += game->board[i][k - 1];
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

int move_right(struct Game *game) {
    int moved = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = COLS - 2; j >= 0; j--) {
            if (game->board[i][j] != 0) {
                int k = j;
                while (k < COLS - 1 && game->board[i][k + 1] == 0) {
                    game->board[i][k + 1] = game->board[i][k];
                    game->board[i][k] = 0;
                    k++;
                    moved = 1;
                }
                if (k < COLS - 1 && game->board[i][k + 1] == game->board[i][k]) {
                    game->board[i][k + 1] *= 2;
                    game->board[i][k] = 0;
                    game->score += game->board[i][k + 1];
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

int game_over(struct Game *game) {
    // Check if the board is full
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (game->board[i][j] == 0) {
                return 0;
            }
        }
    }

    // Check if user can do any movement
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int current_tile = game->board[i][j];
            if (i > 0 && game->board[i - 1][j] == current_tile) {
                return 0;
            }
            if (i < ROWS - 1 && game->board[i + 1][j] == current_tile) {
                return 0;
            }
            if (j > 0 && game->board[i][j - 1] == current_tile) {
                return 0;
            }
            if (j < COLS - 1 && game->board[i][j + 1] == current_tile) {
                return 0;
            }
        }
    }

    return 1;
}