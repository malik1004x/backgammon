#pragma once

#include <ncurses.h>

#define BOARD_DEFAULT                                                          \
  "00002000000000510031000000505100000030005000000000210000000"

void startGame(struct menu *menu, WINDOW *boardWindow, struct board *board);

void replayGame(struct menu *menu, WINDOW *boardWindow, struct board *board);

void startNewGame(struct menu *menu, WINDOW *boardWindow, struct board *board);

void promptLoadAndStart(struct menu *menu, WINDOW *boardWindow,
                        struct board *board);
