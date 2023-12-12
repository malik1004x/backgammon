#include <ncurses.h>
#include "print.h"
#include <stdlib.h>
#include "save.h"
#include "dice.h"
#include "menu.h"
#include "backgammon.h"
#include "structs.h"
#include "start.h"
#include "move.h"

void startGame(struct menu *menu, WINDOW *boardWindow, struct board *board) {
  printMatchScore(board);
  printBoard(boardWindow, board);
  printDice((*board).move.moves, -1);
  int winner;
  if((winner = checkWinner(board)) != -1) showResults(boardWindow, board, menu, winner, 0);
  else loadMenu(menu, playing);
}

void replayGame(struct menu *menu, WINDOW *boardWindow, struct board *board) {
  int won[2];
  won[0] = (*board).won[0];
  won[1] = (*board).won[1];
  loadBoard(BOARD_DEFAULT, board);
  rollDice((*board).move.moves);
  (*board).move.player = rand() % 2;
  (*board).won[0] = won[0];
  (*board).won[1] = won[1];
  startGame(menu, boardWindow, board);
}

void startNewGame(struct menu *menu, WINDOW *boardWindow, struct board *board) {
  loadBoard(BOARD_DEFAULT, board);
  rollDice((*board).move.moves);
  (*board).move.player = rand() % 2;
  startGame(menu, boardWindow, board);
}

void promptLoadAndStart(struct menu *menu, WINDOW *boardWindow,
                        struct board *board) {
  promptLoad(board);
  startGame(menu, boardWindow, board);
}
