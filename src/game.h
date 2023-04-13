#ifndef GAME_H
#define GAME_H

#define ROWS 4
#define COLS 4

struct Game {
    int board[ROWS][COLS];
    int score;
};

void init_game(struct Game *game);

void spawn_number(struct Game *game);

int move_up(struct Game *game);

int move_down(struct Game *game);

int move_left(struct Game *game);

int move_right(struct Game *game);

int game_over(struct Game *game);

#endif