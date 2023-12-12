#pragma once

#define BOARD_SIZE 24

#define BOARD_WINDOW_WIDTH 26
#define BOARD_WINDOW_HEIGHT 17
#define BOARD_WINDOW_Y 1
#define BOARD_WINDOW_X 10

#define HIGHLIGHTED_DICE_COLORPAIR 1

#define NUMBER_OF_DICE 2

#define other(p) (p) ? 0 : 1

#define MENU_WINDOW_WIDTH 8
#define MENU_WINDOW_HEIGHT 8
#define MENU_WINDOW_Y 3
#define MENU_WINDOW_X 45
#define INFO_Y 10
#define INFO_X 10

int min(int a, int b);

void printInfo(void);

void initCurses(void);
