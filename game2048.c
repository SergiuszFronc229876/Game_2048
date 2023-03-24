#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game2048.h"
#include "oled.h"
/*
 * Move tiles on board in given direction
 */
int move(int board[][BOARD_SIDE_SIZE], enum directions direction) {
    int moved = 0;
    switch (direction) {
        case LEFT:
            for (int y = 0; y < BOARD_SIDE_SIZE; ++y) {
                for (int x = 0; x < BOARD_SIDE_SIZE - 1; ++x) {
                    for (int k = x + 1; k < BOARD_SIDE_SIZE; ++k) {
                        if (board[k][y] == 0) {
                            continue;
                        } else if (board[k][y] == board[x][y]) {
                            board[x][y] *= 2;
                            board[k][y] = 0;
                            moved = 1;
                            break;
                        } else if (board[x][y] == 0) {
                            board[x][y] = board[k][y];
                            board[k][y] = 0;
                            moved = 1;
                        } else {
                            break;
                        }
                    }
                }
            }
            break;
        case RIGHT:
            for (int y = 0; y < BOARD_SIDE_SIZE; ++y) {

                for (int x = BOARD_SIDE_SIZE - 1; x >= 1; --x) {
                    for (int k = x - 1; k >= 0; --k) {
                        if (board[k][y] == 0) {
                            continue;
                        } else if (board[k][y] == board[x][y]) {
                            board[x][y] *= 2;
                            board[k][y] = 0;
                            moved = 1;
                            break;
                        } else if (board[x][y] == 0) {
                            board[x][y] = board[k][y];
                            board[k][y] = 0;
                            moved = 1;
                        } else {
                            break;
                        }
                    }
                }
            }
            break;
        case UP:
            for (int x = 0; x < BOARD_SIDE_SIZE; ++x) {
                for (int y = 0; y < BOARD_SIDE_SIZE - 1; ++y) {
                    for (int k = y + 1; k < BOARD_SIDE_SIZE; ++k) {
                        if (board[x][k] == 0) {
                            continue;
                        } else if (board[x][k] == board[x][y]) {
                            board[x][y] *= 2;
                            board[x][k] = 0;
                            moved = 1;
                            break;
                        } else if (board[x][y] == 0) {
                            board[x][y] = board[x][k];
                            board[x][k] = 0;
                            moved = 1;
                        } else {
                            break;
                        }
                    }
                }
            }
            break;
        case DOWN:
            for (int x = 0; x < BOARD_SIDE_SIZE; ++x) {
                for (int y = BOARD_SIDE_SIZE - 1; y >= 1; --y) {
                    for (int k = y - 1; k >= 0; --k) {
                        if (board[x][k] == 0) {
                            continue;
                        } else if (board[x][k] == board[x][y]) {
                            board[x][y] *= 2;
                            board[x][k] = 0;
                            moved = 1;
                            break;
                        } else if (board[x][y] == 0) {
                            board[x][y] = board[x][k];
                            board[x][k] = 0;
                            moved = 1;
                        } else {
                            break;
                        }
                    }
                }
            }
            break;
        default:
            printf("Error: invalid 'direcation' argument value '%c'\n", direction);
            exit(1);
    }
    if (moved == 1) {
        generateNewTile(board);
    }
    return moved;
}

/*
 * Generate first two values
 */
void initBoard(int board[][BOARD_SIDE_SIZE]) {
    int first_x = rand() % BOARD_SIDE_SIZE;
    int first_y = rand() % BOARD_SIDE_SIZE;
    int value_prob = rand() % 100; // losowanie 2 lub 4, szansa na 2 to 80%
    board[first_x][first_y] = (value_prob < 80) ? 2 : 4;

    for (;;) {
        int second_x = rand() % BOARD_SIDE_SIZE;
        int second_y = rand() % BOARD_SIDE_SIZE;
        if (!(second_x == first_x && first_y == second_y)) {
            board[second_x][second_y] = 2;
            break;
        }
    }
}

/*
 * Initialize game
 */
void initGame(int board[BOARD_SIDE_SIZE][BOARD_SIDE_SIZE]) {
    srand(time(NULL));
    for (int i = 0; i < BOARD_SIDE_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIDE_SIZE; ++j) {
            board[i][j] = 0;
        }
    }
    initBoard(board);
}

/*
 * Generate value after move
 */
void generateNewTile(int board[][BOARD_SIDE_SIZE]) {
    int zero_x[BOARD_SIDE_SIZE * BOARD_SIDE_SIZE];
    int zero_y[BOARD_SIDE_SIZE * BOARD_SIDE_SIZE];
    int counter = 0;
    for (int i = 0; i < BOARD_SIDE_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIDE_SIZE; ++j) {
            if (board[i][j] == 0) {
                zero_x[counter] = i;
                zero_y[counter] = j;
                counter++;
            }
        }
    }
    int x = zero_x[rand() % counter];
    int y = zero_y[rand() % counter];

    board[x][y] = (rand() % 100) < 80 ? 2 : 4;
}

/*
 * Draw empty board, only lines
 */
void drawEmptyBoard() {
	for (int y = 0; y < BOARD_PIXEL_SIZE_Y; ++y) {
        for (int x = 0; x < BOARD_PIXEL_SIZE_X; ++x) {
            cur_frame[x][y] = 0;
        	if (x % 18 == 0 || y % 8 == 0) {
                oled_putPixel(x, y, OLED_COLOR_WHITE);
                cur_frame[x][y] = 1;
            }
        }
        oled_putPixel(BOARD_PIXEL_SIZE_X, y, OLED_COLOR_WHITE);
        cur_frame[BOARD_PIXEL_SIZE_X][y] = 1;
    }
    for (int x = 0; x <= BOARD_PIXEL_SIZE_X; ++x) {
        oled_putPixel(x, BOARD_PIXEL_SIZE_Y, OLED_COLOR_WHITE);
        cur_frame[x][BOARD_PIXEL_SIZE_Y] = 1;
    }
}

/*
 * Draw every tile value on board
 */
void drawTilesOnBoard(int board[][BOARD_SIDE_SIZE]) {
    // clear new_frame array
	for (int y = 0; y < BOARD_PIXEL_SIZE_Y; ++y) {
		for (int x = 0; x < BOARD_PIXEL_SIZE_X; ++x) {
			new_frame[x][y] = 0;
			if (x % 18 == 0 || y % 8 == 0) {
				new_frame[x][y] = 1;
			}
			new_frame[BOARD_PIXEL_SIZE_X][y] = 1;

		}
	}
	for (int x = 0; x <= BOARD_PIXEL_SIZE_X; ++x) {
		new_frame[x][BOARD_PIXEL_SIZE_Y] = 1;
	}

	// put white pixels position in new_frame
    for (int i = 0; i < BOARD_SIDE_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIDE_SIZE; ++j) {
            drawTile(board[i][j], (i * 18) + 2, (j * 8) + 2);
        }
    }

    // compare changes in cur_frame and new_frame
	for (int y = 0; y < BOARD_PIXEL_SIZE_Y; ++y) {
        for (int x = 0; x < BOARD_PIXEL_SIZE_X; ++x) {
			if (new_frame[x][y] != cur_frame[x][y]) {
				cur_frame[x][y] = new_frame[x][y];
				oled_putPixel(x, y, cur_frame[x][y] == 1 ? OLED_COLOR_WHITE : OLED_COLOR_BLACK);
			}
		}
	}
}

/*
 * Draw a single tile value on board at specified place
 */
void drawTile(int tileValue, int x, int y) {
    if (tileValue > 9999) {
        printf("Error: Can't operate on numbers with more than 4 digits");
        exit(1);
    }
    for (int i = 0; i < 4; ++i) {
        int digit = tileValue % 10;
        if (tileValue != 0) {
            drawDigit(digit, x + 12 - (i * 4), y);
        }
        tileValue /= 10;
    }
}

/*
 * Draw a single digit from tile value
 */
void drawDigit(int digit, int x, int y) {
    int (*digit_scheme)[3];

    switch (digit) {
        case 0:
            digit_scheme = zero;
            break;
        case 1:
            digit_scheme = one;
            break;
        case 2:
            digit_scheme = two;
            break;
        case 3:
            digit_scheme = three;
            break;
        case 4:
            digit_scheme = four;
            break;
        case 5:
            digit_scheme = five;
            break;
        case 6:
            digit_scheme = six;
            break;
        case 7:
            digit_scheme = seven;
            break;
        case 8:
            digit_scheme = eight;
            break;
        case 9:
            digit_scheme = nine;
            break;
        default:
            printf("Error: printDigitException: wrong argument value. 'digit' has to be a number from o to 9 not '%d'",
                   digit);
            exit(1);
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
//            oled_putPixel(x + j, y + i, digit_scheme[i][j] == 1 ? OLED_COLOR_WHITE : OLED_COLOR_BLACK);
            if (digit_scheme[i][j] == 1) {
            	new_frame[x + j][y + i] = 1;
            }
        }
    }
}

void drawBoardOled(int board[][BOARD_SIDE_SIZE]) {
    drawEmptyBoard();
    drawTilesOnBoard(board);
}

/*
 * Print board to console
 */
void printBoardConsole(int board[][BOARD_SIDE_SIZE]) {
    for (int i = 0; i < BOARD_SIDE_SIZE; ++i) {
        printf(" ----------------------------\n");
        for (int j = 0; j < BOARD_SIDE_SIZE; ++j) {
            if (board[i][j] == 0) {
                printf(" |     ");
            } else if (board[i][j] < 10) {
                printf(" |    %d", board[i][j]);
            } else if (board[i][j] < 100) {
                printf(" |  %d", board[i][j]);
            } else {
                printf(" | %d", board[i][j]);
            }
        }
        printf("|\n");
    }
    printf(" ----------------------------\n");
}
