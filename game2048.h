#ifndef SYSWBUD_GAME2048_H
#define SYSWBUD_GAME2048_H

#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIDE_SIZE 4
#define BOARD_PIXEL_SIZE_X BOARD_SIDE_SIZE * (4 * 3 + 3 + 3)
#define BOARD_PIXEL_SIZE_Y BOARD_SIDE_SIZE * (5 + 3)

enum directions {
    LEFT, RIGHT, UP, DOWN
};

int cur_frame[BOARD_PIXEL_SIZE_X][BOARD_PIXEL_SIZE_Y];
int new_frame[BOARD_PIXEL_SIZE_X][BOARD_PIXEL_SIZE_Y];

void generateNewTile(int board[][BOARD_SIDE_SIZE]);

void initBoard(int board[][BOARD_SIDE_SIZE]);

void initGame();

int move(int board[][BOARD_SIDE_SIZE], enum directions direction);

void drawEmptyBoard();

void drawTilesOnBoard(int board[][BOARD_SIDE_SIZE]);

void drawTile(int tileValue, int x, int y);

void drawDigit(int digit, int x, int y);

void drawBoardOled(int board[][BOARD_SIDE_SIZE]);

void printBoardConsole(int board[][BOARD_SIDE_SIZE]);

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

#endif //SYSWBUD_GAME2048_H
