#ifndef GRA_2048_GAME_OLED_CONTROLLER_H
#define GRA_2048_GAME_OLED_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "oled.h"

#define BOARD_PIXEL_SIZE_X COLS * (4 * 3 + 3 + 3) + 1
#define BOARD_PIXEL_SIZE_Y ROWS * (5 + 3) + 1

int cur_frame[BOARD_PIXEL_SIZE_X][BOARD_PIXEL_SIZE_Y];
int new_frame[BOARD_PIXEL_SIZE_X][BOARD_PIXEL_SIZE_Y];

void draw_empty_board();

void draw_board(int board[ROWS][COLS]);

// TE WARTOSCI SA WYKORZYSTYWANE W game_oled_controller.c!
static int zero[5][3] = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static int one[5][3] = {
        {0, 0, 1},
        {0, 1, 1},
        {1, 0, 1},
        {0, 0, 1},
        {0, 0, 1}
};

static int two[5][3] = {
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1}
};

static int three[5][3] = {
        {1, 1, 1},
        {0, 0, 1},
        {0, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
};

static int four[5][3] = {
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1}
};

static int five[5][3] = {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
};

static int six[5][3] = {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static int seven[5][3] = {
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1}
};

static int eight[5][3] = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static int nine[5][3] = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
};

#endif
