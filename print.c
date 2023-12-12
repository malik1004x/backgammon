#include<ncurses.h>
#include "print.h"
#include "structs.h"
#include "backgammon.h"
#include "strings.h"

void printMatchScore(struct board *board) {
  mvprintw(MATCHSCORE_Y, MATCHSCORE_X, MATCHSCORE_FORMAT, (*board).won[0],
           (*board).won[1]);
}

void printField(WINDOW *window, int player, int pieces, int y, int x,
                int direction) {
  char piece, dualPiece;
  if (player) {
    piece = PLAYER1_PIECE;
    dualPiece = PLAYER1_DUALPIECE;
  } else {
    piece = PLAYER0_PIECE;
    dualPiece = PLAYER0_DUALPIECE;
  }

  for (int i = 0; i < min(pieces, MAX_FIELDLENGTH); i++) {
    mvwaddch(window, y, x, piece);
    y += direction;
  }

  if (pieces > MAX_FIELDLENGTH) {
    y -= direction * MAX_FIELDLENGTH;
    for (int i = 0; i < pieces - MAX_FIELDLENGTH; i++) {
      mvwaddch(window, y, x, dualPiece);
      y += direction;
    }
  } else {
    for (int i = pieces; i < MAX_FIELDLENGTH; i++) {
      mvwaddch(window, y, x, EMPTY_SPOT);
      y += direction;
    }
  }
}

void printBar(WINDOW *window, const int *bar, int y, int x) {
  for (int i = 0; i < 2; i++) {
    mvwaddch(window, y++, x, BAR_TOPCHAR);
    for (int j = 0; j < bar[i]; j++) {
      mvwaddch(window, y++, x, i ? PLAYER1_PIECE : PLAYER0_PIECE);
    }
    for (int j = 0; j < (BOARD_WINDOW_HEIGHT / 2) - bar[i] - 2; j++) {
      mvwaddch(window, y++, x, BAR_MIDDLECHAR);
    }
    mvwaddch(window, y++, x, BAR_BOTTOMCHAR);
    mvwaddch(window, y++, x, ' ');
  }
}

void printOutside(struct board *board) {
  mvprintw(OUTSIDE_Y, OUTSIDE_X, OUTSIDE_LABEL);

  move(OUTSIDE_Y + 1, OUTSIDE_X);
  clrtoeol();
  move(OUTSIDE_Y + 2, OUTSIDE_X);
  clrtoeol();

  for (int i = 0; i < (*board).outside[0]; i++)
    mvaddch(OUTSIDE_Y + 1, OUTSIDE_X + i, PLAYER0_PIECE);

  for (int i = 0; i < (*board).outside[1]; i++)
    mvaddch(OUTSIDE_Y + 2, OUTSIDE_X + i, PLAYER1_PIECE);
}

void printPlayer(int player) {
  mvprintw(PLAYERDISPLAY_Y, PLAYERDISPLAY_X, "Player %d", player + 1);
}

void printBoard(WINDOW *window, struct board *board) {
  werase(window);
  int direction = -1;
  // starting at the bottom right corner.
  int y = BOARD_WINDOW_HEIGHT - 1;
  int x = BOARD_WINDOW_WIDTH - 1;

  for (int i = 0; i < 2; i++) {
    for (int j = (BOARD_SIZE / 2) * i; j < (BOARD_SIZE / 2) * (i + 1); j++) {
      printField(window, (*board).fields[j].player, (*board).fields[j].pieces,
                 y, x, direction);
      x += 2 * direction;
    }
    x -= 2 * direction;
    y = 0;
    direction = 1;
  }

  printBar(window, (*board).bar, 0, (BOARD_WINDOW_WIDTH / 2) + 1);
  printOutside(board);
  printPlayer((*board).move.player);
  wrefresh(window);
  refresh();
}

void printDice(int *moves, int highlight) {
  move(DICE_Y, DICE_X);
  for (int i = 0; i < NUMBER_OF_DICE; i++) {
    if (i == highlight)
      attron(COLOR_PAIR(HIGHLIGHTED_DICE_COLORPAIR));
    printw("[%d] ", moves[i]);
    if (i == highlight)
      attroff(COLOR_PAIR(HIGHLIGHTED_DICE_COLORPAIR));
  }
  refresh();
}
