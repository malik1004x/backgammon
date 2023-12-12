#pragma once

#include <ncurses.h>

struct board;
struct menu;

int checkWinner(struct board *board);

int canRemovePiece(struct board *board, int source, int player);

int hasUnusedHit(struct board *board, int source, int destination, int player);

int isLegalMove(struct board *board, int source, int destination, int player);

void makeMove(struct board *board, int source, int destination);

void removeFromBar(struct board *board, int player, int diceResult);

void promptMove(struct board *board, int player, int diceResult);

int getPoints(struct board *board, int winner);

void showResults(WINDOW *boardWindow, struct board *board, struct menu *menu,
                 int winner, int update);

void moveLoop(struct menu *menu, WINDOW *boardWindow, struct board *board);
