#include "fame.h"
#include <ncurses.h>
#include "prompt.h"
#include <string.h>
#include "strings.h"

void initFame(void) {
  FILE* file;
  file = fopen(FAMEFILE_NAME, "r");
  if(file) return; // not initting if there's already something there.
  
  file = fopen(FAMEFILE_NAME, "w");

  for(int i=0; i<FAMELEN; i++) {
    fprintf(file, "%s %d\n", FAME_DEFAULT_NAME, 0);
  }

  fclose(file);
}

void loadFame(struct hallOfFame *destination) {
  FILE* file;
  file = fopen(FAMEFILE_NAME, "r");
  for(int i=0; i<FAMELEN; i++) {
    fscanf(file, "%s%d", (*destination).names[i], (&(*destination).scores[i]));
  }
}

void printFame(void) {
  struct hallOfFame fame;
  loadFame(&fame);

  WINDOW* fameWin = newwin(FAME_WINDOW_HEIGHT, FAME_WINDOW_WIDTH,
                              FAME_WINDOW_Y, FAME_WINDOW_X);

  box(fameWin, 0, 0);

  mvwprintw(fameWin, 1, 1, FAME_WINDOW_HEADER);

  for(int i=0; i<FAMELEN; i++) {
    mvwprintw(fameWin, i+2, 1, "%s:     %d", fame.names[i], fame.scores[i]);
  }
  wrefresh(fameWin);
  getch();
  wclear(fameWin);
  wrefresh(fameWin);
  delwin(fameWin);
}

void sortTempFame(int tempScores[FAMELEN+1], char tempNames[FAMELEN+1][FAMENAME_MAXLENGTH+1]) {
  char nameSwap[FAMENAME_MAXLENGTH];
  int scoreSwap;
  for (int i=0; i<FAMELEN+1; i++) {
    for (int j=i+1; j<FAMELEN+1; j++) {
      if(tempScores[j] > tempScores[i]) {
        scoreSwap = tempScores[i];
        tempScores[i] = tempScores[j];
        tempScores[j] = scoreSwap;

        strcpy(nameSwap, tempNames[i]);
        strcpy(tempNames[i], tempNames[j]);
        strcpy(tempNames[j], nameSwap);
      }
    }
  }
}

void saveFame(struct hallOfFame *source) {
  FILE* file;

  file = fopen(FAMEFILE_NAME, "w");

  for(int i=0; i<FAMELEN; i++) {
    fprintf(file, "%s %d\n", (*source).names[i], (*source).scores[i]);
  }

  fclose(file);
}

void updateFame(int score) {
  struct hallOfFame fame;
  loadFame(&fame);
  char tempNames[FAMELEN+1][FAMENAME_MAXLENGTH+1];
  int tempScores[FAMELEN+1];

  for (int i=0; i<FAMELEN; i++) {
    strcpy(tempNames[i], fame.names[i]);
    tempScores[i] = fame.scores[i];
  }
  // this is the new entry. later we'll see if we need to get a name
  tempNames[FAMELEN][0] = '\0';
  tempScores[FAMELEN] = score;

  sortTempFame(tempScores, tempNames);

  int toSave = 0; // we don't save if nothing changed.
  for(int i=0; i<FAMELEN; i++) {
    if(tempNames[i][0] == '\0') { // if this is the new score
      prompt(PROMPT_FAME, "%s", tempNames[i]);
      toSave = 1;
    }
      
    strcpy(fame.names[i],tempNames[i]);
    fame.scores[i] = tempScores[i];
  }

  if(toSave) saveFame(&fame);
}
