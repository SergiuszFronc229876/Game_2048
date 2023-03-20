#ifndef GAME_H
#define GAME_H

#define ROWS 4
#define COLS 4

struct Game {
    int board[ROWS][COLS];
    int score;
};

void spawn_number(struct Game *game);
void draw_board(struct Game *game);
void move_up(struct Game *game);
void move_down(struct Game *game);
void move_left(struct Game *game);
void move_right(struct Game *game);

#endif /* GAME_H */