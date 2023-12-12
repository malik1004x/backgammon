#include "dice.h"
#include "structs.h"
#include <stdlib.h>
#include "print.h"

void rollDice(int *moves) {
  moves[0] = (rand() % 5) + 1;
  moves[1] = (rand() % 5) + 1;
  if (moves[0] == moves[1]) {
    moves[2] = moves[0];
    moves[3] = moves[0];
  } else {
    moves[2] = 0;
    moves[3] = 0;
  }
}

void swapDice(struct board *board) {
  int tmp = (*board).move.moves[0];
  (*board).move.moves[0] = (*board).move.moves[1];
  (*board).move.moves[1] = tmp;
  printDice((*board).move.moves, -1);
}
