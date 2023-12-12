#include "backgammon.h"
#include <ncurses.h>
#include <stdlib.h>
#include "structs.h"
#include "save.h"
#include "fame.h"
#include <time.h>
#include "menu.h"
#include "strings.h"

int min(int a, int b) { return a < b ? a : b; }

void printInfo(void) {
  mvprintw(INFO_Y, INFO_X, PRODUCT_NAME);
  mvprintw(INFO_Y + 1, INFO_X, COPYRIGHT_INFO);
  refresh();
}

void initCurses(void) {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  start_color();
  init_pair(HIGHLIGHTED_DICE_COLORPAIR, COLOR_GREEN, COLOR_BLACK);
}

int main(void) {
  srand(time(NULL));
  clearTemp();
  struct menu currentMenu;
  struct board currentBoard;
  initFame();
  loadMenu(&currentMenu, mainMenu);
  initCurses();
  printInfo();
  WINDOW *menuWindow = newwin(MENU_WINDOW_HEIGHT, MENU_WINDOW_WIDTH,
                              MENU_WINDOW_Y, MENU_WINDOW_X);
  WINDOW *boardWindow = newwin(BOARD_WINDOW_HEIGHT, BOARD_WINDOW_WIDTH,
                               BOARD_WINDOW_Y, BOARD_WINDOW_X);

  menuLoop(menuWindow, &currentMenu, boardWindow, &currentBoard);
  endwin();
  return 0;
}
