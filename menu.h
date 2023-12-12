#pragma once

#include <ncurses.h>

struct board;

#define MENU_EXIT "Exit"
#define MENU_NEWGAME "Start"
#define MENU_LOADGAME "Load"
#define MENU_LOADREPLAY "Watch"
#define MENU_ROLLDICE "Move"
#define MENU_SWAPDICE "Swap"
#define MENU_SAVEGAME "Save"
#define MENU_REMATCH "Rematch"
#define MENU_FAME "Fame"
#define MENU_MAIN                                                              \
  { MENU_NEWGAME, MENU_LOADGAME, MENU_LOADREPLAY, MENU_FAME, MENU_EXIT }
#define MENU_INGAME                                                            \
  { MENU_ROLLDICE, MENU_SWAPDICE, MENU_SAVEGAME, MENU_EXIT }
#define MENU_RESULTS                                                           \
  { MENU_REMATCH, MENU_SAVEGAME, MENU_EXIT }
#define MENU_SELECTEDCHAR '>'
#define MENU_UNSELECTEDCHAR ' '
#define MENU_MAXOPT 5
#define MENU_OPTIONLENGTH 10

enum gameStates { mainMenu, playing, results };

struct menu {
  int selected;
  char options[MENU_MAXOPT][MENU_OPTIONLENGTH];
  enum gameStates state;
};

void loadMenu(struct menu *menu, enum gameStates state);

void menuSelectedMain(struct menu *menu, WINDOW *bWindow, struct board *board);

void menuSelectedPlaying(struct menu *menu, WINDOW *bWindow,
                         struct board *board);

void menuSelectedResults(struct menu *menu, WINDOW *bWindow,
                         struct board *board);

void menuSelected(struct menu *menu, WINDOW *bWindow, struct board *board);

void printMenu(WINDOW *window, struct menu *menu, int y, int x);

void menuLoop(WINDOW *window, struct menu *menu, WINDOW *boardWindow,
              struct board *board);
