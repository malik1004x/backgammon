#include <ncurses.h>
#include "prompt.h"
#include "replay.h"
#include "structs.h"
#include "print.h"
#include "save.h"
#include "strings.h"

void showReplay(WINDOW *boardWindow, struct board *board, FILE *file) {
  char boardString[SAVELEN + 1];
  boardString[SAVELEN] = '\0';
  keypad(stdscr, 1);
  while (1) {

    fscanf(file, "%s\n", boardString);
    fseek(file, ftell(file) - SAVELEN - 1, SEEK_SET);
    loadBoard(boardString, board);
    printDice((*board).move.moves, -1);
    printMatchScore(board);
    printBoard(boardWindow, board);

    switch (getch()) {
    case KEY_DOWN:
      fseek(file, SAVELEN + 1, SEEK_CUR);
      break;
    case KEY_UP:
      fseek(file, -SAVELEN - 1, SEEK_CUR);
      break;
    case KEY_LEFT:
      rewind(file);
      break;
    case KEY_RIGHT:
      fseek(file, -SAVELEN - 1, SEEK_END);
      break;
    default:
      continue;
    }
  }
}

void promptReplay(WINDOW *boardWindow, struct board *board) {
  char filename[FILENAME_MAXLENGTH];
  FILE *file;
  int firstAttempt = 1;
  do {
    prompt(firstAttempt ? PROMPT_REPLAY : PROMPT_LOAD_INVALID, "%s", filename);
    file = fopen(filename, "r");
    firstAttempt = 0;
  } while (!file);

  showReplay(boardWindow, board, file);
}
