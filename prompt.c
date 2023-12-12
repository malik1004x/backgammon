#include <ncurses.h>
#include "prompt.h"

void prompt(const char *prompt, char *format, void *destination) {
  move(PROMPTER_Y, PROMPTER_X);
  clrtoeol();
  nocbreak();
  echo();
  printw("%s", prompt);
  scanw(format, destination);
  cbreak();
  noecho();
  // below ensures the prompter disappears after the user's done w/ it
  move(PROMPTER_Y, PROMPTER_X);
  clrtoeol();
  refresh();
}
