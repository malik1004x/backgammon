#pragma once

#include <ncurses.h>

struct board;

void showReplay(WINDOW *boardWindow, struct board *board, FILE *file);

void promptReplay(WINDOW *boardWindow, struct board *board);
