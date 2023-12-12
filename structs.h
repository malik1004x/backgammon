#pragma once
#include "backgammon.h"

// represents one field on the board.
struct field {
  int pieces;
  int player; // 0 or 1, which player do the pieces belong to
};

// represents the currently played move.
struct move {
  int moves[NUMBER_OF_DICE * 2];
  int player; // 0 or 1
};

// represents the entire board
struct board {
  struct field fields[24];
  struct move move;
  int outside[2];
  int bar[2];
  int won[2];
};
