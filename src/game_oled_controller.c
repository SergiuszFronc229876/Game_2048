#include "game_oled_controller.h"

/*
 * Draw empty board, only lines
 */
void draw_empty_board() {
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
void draw_all_tiles(int board[ROWS][COLS]) {
    // clear new_frame array and set empty grid layout
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

	// Set digit pixel positions to new_frame
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            draw_tile(board[j][i], (i * 18) + 2, (j * 8) + 2);
        }
    }
    printf("\n");

    // Compare changes in cur_frame and new_frame and draw pixels on OLED screen
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
void draw_tile(int tileValue, int x, int y) {
    if (tileValue > 9999) {
        printf("Error: Can't operate on numbers with more than 4 digits");
        exit(1);
    }
    for (int i = 0; i < 4; ++i) {
        int digit = tileValue % 10;
        if (tileValue != 0) {
            draw_digit(digit, x + 12 - (i * 4), y);
        }
        tileValue /= 10;
    }
}

/*
 * Draw a single digit in a tile
 */
void draw_digit(int digit, int x, int y) {
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
            printf("DrawDigitException: '%d' is wrong value. Argument has to be a integer from 0 to 9", digit);
            exit(1);
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (digit_scheme[i][j] == 1) {
                new_frame[x + j][y + i] = 1;
            }
        }
    }
}

/*
 * Draw whole game on OLED screen
 */
void draw_board(int board[ROWS][COLS]) {
    draw_all_tiles(board);
}

/*
 * Print board to console
 */
void print_board_console(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        printf(" ----------------------------\n");
        for (int j = 0; j < COLS; ++j) {
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
