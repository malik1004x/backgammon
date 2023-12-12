#pragma once

#include <ncurses.h>

struct board;

#define MAX_FIELDLENGTH 8
#define PLAYER0_PIECE 'x'
#define PLAYER1_PIECE 'o'
#define PLAYER0_DUALPIECE 'X'
#define PLAYER1_DUALPIECE 'O'
#define EMPTY_SPOT '.'

#define BAR_TOPCHAR '_'
#define BAR_BOTTOMCHAR '_'
#define BAR_MIDDLECHAR '|'

#define OUTSIDE_LABEL "Outside: "
#define OUTSIDE_Y 15
#define OUTSIDE_X 45

#define MATCHSCORE_Y 0
#define MATCHSCORE_X 15

#define PLAYERDISPLAY_Y 14
#define PLAYERDISPLAY_X 45

#define DICE_Y 14
#define DICE_X 55

void printMatchScore(struct board *board);

void printField(WINDOW *window, int player, int pieces, int y, int x,
                int direction);

void printBar(WINDOW *window, const int *bar, int y, int x);

void printOutside(struct board *board);

void printPlayer(int player);

void printBoard(WINDOW *window, struct board *board);

void printDice(int *moves, int highlight);
