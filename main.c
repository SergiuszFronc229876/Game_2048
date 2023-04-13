#include <stdint.h>
#include <unistd.h>
#include "stdio.h"

#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"

#include "joystick.h"
#include "oled.h"

#include "game.h"
#include "game_oled_controller.h"


#define NOTE_PIN_HIGH() GPIO_SetValue(0, 1<<26);
#define NOTE_PIN_LOW()  GPIO_ClearValue(0, 1<<26);

// ####################################################

static void init_i2c(void) {
    PINSEL_CFG_Type PinCfg;

    /* Initialize I2C2 pin connect */
    PinCfg.Funcnum = 2;
    PinCfg.Pinnum = 10;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 11;
    PINSEL_ConfigPin(&PinCfg);

    // Initialize I2C peripheral
    I2C_Init(LPC_I2C2, 100000);

    /* Enable I2C1 operation */
    I2C_Cmd(LPC_I2C2, ENABLE);
}

static void init_ssp(void) {
    SSP_CFG_Type SSP_ConfigStruct;
    PINSEL_CFG_Type PinCfg;

    /*
     * Initialize SPI pin connect
     * P0.7 - SCK;
     * P0.8 - MISO
     * P0.9 - MOSI
     * P2.2 - SSEL - used as GPIO
     */
    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Portnum = 0;
    PinCfg.Pinnum = 7;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 8;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 9;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Funcnum = 0;
    PinCfg.Portnum = 2;
    PinCfg.Pinnum = 2;
    PINSEL_ConfigPin(&PinCfg);

    SSP_ConfigStructInit(&SSP_ConfigStruct);

    // Initialize SSP peripheral with parameter given in structure above
    SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

    // Enable SSP peripheral
    SSP_Cmd(LPC_SSP1, ENABLE);

}

static int game_move(uint8_t joyState, struct Game *game) {
    static int wait = 0;
    int moved = 0;

    if ((joyState & JOYSTICK_CENTER) != 0) {
        oled_clearScreen(OLED_COLOR_BLACK);
        return moved;
    }

    if (wait++ < 3)
        return moved;

    wait = 0;
    if ((joyState & JOYSTICK_UP) != 0) {
        moved = move_up(game);
    }
    if ((joyState & JOYSTICK_DOWN) != 0) {
        moved = move_down(game);
    }
    if ((joyState & JOYSTICK_LEFT) != 0) {
        moved = move_left(game);
    }
    if ((joyState & JOYSTICK_RIGHT) != 0) {
        moved = move_right(game);
    }
    return moved;
}

static void drawOled(int board[][BOARD_SIDE_SIZE]) {
    drawTilesOnBoard(board);
}

// ##########################################
#define NOTE_PIN_HIGH() GPIO_SetValue(0, 1<<26);
#define NOTE_PIN_LOW()  GPIO_ClearValue(0, 1<<26);
static uint32_t notes[] = {
        2272, // A - 440 Hz
        2024, // B - 494 Hz
        3816, // C - 262 Hz
        3401, // D - 294 Hz
        3030, // E - 330 Hz
        2865, // F - 349 Hz
        2551, // G - 392 Hz
        1136, // a - 880 Hz
        1012, // b - 988 Hz
        1912, // c - 523 Hz
        1703, // d - 587 Hz
        1517, // e - 659 Hz
        1432, // f - 698 Hz
        1275, // g - 784 Hz
};

static void playNote(uint32_t note, uint32_t durationMs) {

    uint32_t t = 0;

    if (note > 0) {

        while (t < (durationMs * 1000)) {
            NOTE_PIN_HIGH();
            Timer0_us_Wait(note / 2);
            //delay32Us(0, note / 2);

            NOTE_PIN_LOW();
            Timer0_us_Wait(note / 2);
            //delay32Us(0, note / 2);

            t += note;
        }

    } else {
        Timer0_Wait(durationMs);
        //delay32Ms(0, durationMs);
    }
}

static uint32_t getNote(uint8_t ch) {
    if (ch >= 'A' && ch <= 'G')
        return notes[ch - 'A'];

    if (ch >= 'a' && ch <= 'g')
        return notes[ch - 'a' + 7];

    return 0;
}

static uint32_t getDuration(uint8_t ch) {
    if (ch < '0' || ch > '9')
        return 400;

    /* number of ms */

    return (ch - '0') * 200;
}

static uint32_t getPause(uint8_t ch) {
    switch (ch) {
        case '+':
            return 0;
        case ',':
            return 5;
        case '.':
            return 20;
        case '_':
            return 30;
        default:
            return 5;
    }
}

static void playSound(uint8_t *song) {
    uint32_t note = 0;
    uint32_t dur = 0;
    uint32_t pause = 0;

    /*
     * A moveSound is a collection of tones where each tone is
     * a note, duration and pause, e.g.
     *
     * "E2,F4,"
     */

    while (*song != '\0') {
        note = getNote(*song++);
        if (*song == '\0')
            break;
        dur = getDuration(*song++);
        if (*song == '\0')
            break;
        pause = getPause(*song++);

        playNote(note, dur);
        //delay32Ms(0, pause);
        Timer0_Wait(pause);
    }
}

static uint8_t *moveSound = (uint8_t *) "A1_";
// ##########################################

int main(void) {

    /* ####### Button ###### */
    /* # */
    uint8_t sw3 = 0;
    uint8_t sw3_pressed;
    /* # */
    /* ##################### */


    /* ####### Accelerometer ###### */
    /* # */
    uint8_t xoff = 0;
    uint8_t yoff = 0;
    uint8_t zoff = 0;

    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t z = 0;

    init_ssp();
    init_i2c();
    acc_init();

    acc_read(&x, &y, &z);
    xoff = 0 - x;
    yoff = 0 - y;
    zoff = 64 - z;
    /* # */
    /* ############################ */


    /* ####### Speaker ####### */
    /* # */
    GPIO_SetDir(2, 1 << 0, 1);
    GPIO_SetDir(2, 1 << 1, 1);

    GPIO_SetDir(0, 1 << 27, 1);
    GPIO_SetDir(0, 1 << 28, 1);
    GPIO_SetDir(2, 1 << 13, 1);
    GPIO_SetDir(0, 1 << 26, 1);

    GPIO_ClearValue(0, 1 << 27); //LM4811-clk
    GPIO_ClearValue(0, 1 << 28); //LM4811-up/dn
    GPIO_ClearValue(2, 1 << 13); //LM4811-shutdn
    /* # */
    /* ####################### */


    /* ####### Joystick and OLED ###### */
    /* # */
    uint8_t joystickState = 0;

    oled_init();
    joystick_init();

    oled_clearScreen(OLED_COLOR_BLACK);

    struct Game game;
    init_game(&game);
    draw_board(game.board);
    /* # */
    /* ################################ */

    int moved = 0;
    while (1) {
        /* ####### Joystick and OLED ###### */
        /* # */
        joystickState = joystick_read();

        if (moved == 0) {
            // When user moved joystick
            if (joystickState != 0) {
                moved = game_move(joystickState, &game);
                if (moved == 1) {
                    drawOled(game.board);
                    playSound(moveSound);
                }
            }
        }
        // When user let go joystick
        if (joystickState == 0) {
            moved = 0;
        }
        /* # */
        /* ################################ */


        /* ####### Button ###### */
        /* # */
        sw3 = ((GPIO_ReadValue(0) >> 4) & 0x01);

        if (sw3 != 0) {
            sw3_pressed = 0;
        }
        if (sw3 == 0 && sw3_pressed == 0) {
            sw3_pressed = 1;
            // Restart the game
            oled_clearScreen(OLED_COLOR_BLACK);
            init_game(&game);
            draw_board(game.board);
        }
        /* # */
        /* ###################### */


        /* ####### Accelerometer ###### */
        /* # */
        acc_read(&x, &y, &z);
        printf("x: %d | y: %d | z: %d\n", x + xoff, y + yoff, z + zoff);
        /* # */
        /* ############################# */

        Timer0_Wait(10);
    }
}

void check_failed(uint8_t *file, uint32_t line) {
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1);
}