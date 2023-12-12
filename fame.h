#pragma once

//#include "consts.h"

#define FAMELEN 3
#define FAMENAME_MAXLENGTH 20
#define FAME_DEFAULT_NAME "Nobody"
#define FAME_WINDOW_HEADER "===HALL OF FAME==="
#define FAMEFILE_NAME "gammonfame"

#define FAME_WINDOW_WIDTH 24
#define FAME_WINDOW_HEIGHT 6
#define FAME_WINDOW_X 45
#define FAME_WINDOW_Y 14

struct hallOfFame {
  char names[FAMELEN][FAMENAME_MAXLENGTH];
  int scores[FAMELEN];
};

void initFame(void);

void loadFame(struct hallOfFame *destination);

void printFame(void);

void sortTempFame(int tempScores[FAMELEN+1], char tempNames[FAMELEN+1][FAMENAME_MAXLENGTH+1]);

void saveFame(struct hallOfFame *source);

void updateFame(int score);
