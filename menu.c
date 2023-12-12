#include "menu.h"
#include <ncurses.h>
#include "save.h"
#include "start.h"
#include "fame.h"
#include "dice.h"
#include <stdlib.h>
#include "move.h"
#include "replay.h"
#include <string.h>

struct board;

void loadMenu(struct menu *menu, enum gameStates state) {
  (*menu).selected = 0;
  (*menu).state = state;
  const char *optMain[MENU_MAXOPT] = MENU_MAIN;
  const char *optPlay[MENU_MAXOPT] = MENU_INGAME;
  const char *optRes[MENU_MAXOPT] = MENU_RESULTS;
  for (int i = 0; i < MENU_MAXOPT; i++) {
    (*menu).options[i][0] = '\0';
    if (state == mainMenu && optMain[i] != NULL)
      strcpy((*menu).options[i], optMain[i]);
    else if (state == playing && optPlay[i] != NULL)
      strcpy((*menu).options[i], optPlay[i]);
    else if (state == results && optRes[i] != NULL)
      strcpy((*menu).options[i], optRes[i]);
  }
}

void menuSelectedMain(struct menu *menu, WINDOW *bWindow, struct board *board) {
  const char *s = (*menu).options[(*menu).selected];
  if (strcmp(s, MENU_EXIT) == 0) {
    endwin();
    exit(0);
  } else if (strcmp(s, MENU_NEWGAME) == 0)
    startNewGame(menu, bWindow, board);
  else if (strcmp(s, MENU_LOADGAME) == 0)
    promptLoadAndStart(menu, bWindow, board);
  else if (strcmp(s, MENU_LOADREPLAY) == 0)
    promptReplay(bWindow, board);
  else if (strcmp(s, MENU_FAME) == 0)
    printFame();
}

void menuSelectedPlaying(struct menu *menu, WINDOW *bWindow,
                         struct board *board) {
  const char *s = (*menu).options[(*menu).selected];
  if (strcmp(s, MENU_EXIT) == 0) {
    endwin();
    exit(0);
  } else if (strcmp(s, MENU_ROLLDICE) == 0)
    moveLoop(menu, bWindow, board);
  else if (strcmp(s, MENU_SWAPDICE) == 0)
    swapDice(board);
  else if (strcmp(s, MENU_SAVEGAME) == 0)
    promptSave();
}

void menuSelectedResults(struct menu *menu, WINDOW *bWindow,
                         struct board *board) {
  const char *s = (*menu).options[(*menu).selected];
  if (strcmp(s, MENU_EXIT) == 0) {
    endwin();
    exit(0);
  } else if (strcmp(s, MENU_REMATCH) == 0)
    replayGame(menu, bWindow, board);
  else if (strcmp(s, MENU_SAVEGAME) == 0)
    promptSave();
}

void menuSelected(struct menu *menu, WINDOW *bWindow, struct board *board) {
  switch ((*menu).state) {
  case mainMenu:
    menuSelectedMain(menu, bWindow, board);
    break;
  case playing:
    menuSelectedPlaying(menu, bWindow, board);
    break;
  case results:
    menuSelectedResults(menu, bWindow, board);
    break;
  }
}

void printMenu(WINDOW *window, struct menu *menu, int y, int x) {
  wclear(window);
  for (int i = 0; i < MENU_MAXOPT; i++) {
    mvwprintw(window, y++, x, "%c%s",
              i == (*menu).selected ? MENU_SELECTEDCHAR : MENU_UNSELECTEDCHAR,
              (*menu).options[i]);
  }
  wrefresh(window);
}

void menuLoop(WINDOW *window, struct menu *menu, WINDOW *boardWindow,
              struct board *board) {
  while (1) {
    printMenu(window, menu, 0, 0);
    keypad(window, 1);
    switch (wgetch(window)) {
    case KEY_UP:
      if ((*menu).selected > 0)
        (*menu).selected--;
      break;
    case KEY_DOWN:
      if ((*menu).options[(*menu).selected + 1][0] != '\0')
        (*menu).selected++;
      break;
    case '\n':
      menuSelected(menu, boardWindow, board);
      break;
    }
  }
}
