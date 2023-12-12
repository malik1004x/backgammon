#include<stdio.h>
#include "save.h"
#include "prompt.h"
#include "structs.h"
#include "strings.h"
#include "backgammon.h"

void loadBoard(const char *bString, struct board *dest) {
  for (int i = 0; i < 2; i++) { // for both players
    (*dest).bar[i] = bString[2 * i] - '0';
    (*dest).outside[i] = bString[2 * i + 1] - '0';
  }

  for (int i = 2; i < BOARD_SIZE + 2; i++) { // i=2 will start at bString[4]
    (*dest).fields[i - 2].pieces = bString[2 * i] - '0';
    (*dest).fields[i - 2].player = bString[2 * i + 1] - '0';
  }

  for (int i = SAVELEN - 7; i < SAVELEN - 3; i++) {
    (*dest).move.moves[i - SAVELEN + 7] = bString[i] - '0';
  }

  (*dest).move.player = bString[SAVELEN - 3] - '0';

  for (int i = SAVELEN - 2; i < SAVELEN; i++) {
    (*dest).won[i - SAVELEN + 2] = bString[i] - '0';
  }
}

void serializeBoard(struct board *board, char *destination) {
  for (int i = 0; i < 2; i++) {
    destination[2 * i] = (*board).bar[i] + '0';
    destination[2 * i + 1] = (*board).outside[i] + '0';
  }

  for (int i = 2; i < BOARD_SIZE + 2; i++) {
    destination[2 * i] = (*board).fields[i - 2].pieces + '0';
    destination[2 * i + 1] = (*board).fields[i - 2].player + '0';
  }

  for (int i = SAVELEN - 7; i < SAVELEN - 3; i++) {
    destination[i] = (*board).move.moves[i - SAVELEN + 7] + '0';
  }

  destination[SAVELEN - 3] = (*board).move.player + '0';

  for (int i = SAVELEN - 2; i < SAVELEN; i++) {
    destination[i] = (*board).won[i - SAVELEN + 2] + '0';
  }
}

void clearTemp(void) {
  FILE *file;
  file = fopen(TEMPFILE_NAME, "w");
  fclose(file);
}

void saveMoveToTemp(struct board *board) {
  char boardString[SAVELEN + 1];
  boardString[SAVELEN] = '\0';
  FILE *file;
  file = fopen(TEMPFILE_NAME, "a");

  serializeBoard(board, boardString);
  fprintf(file, "%s\n", boardString);

  fclose(file);
}

void saveBoardToFile(char *path) {
  FILE *tmpFile, *destFile;
  tmpFile = fopen(TEMPFILE_NAME, "r");
  destFile = fopen(path, "w");

  char buffer;
  while ((buffer = fgetc(tmpFile)) != EOF)
    fputc(buffer, destFile);

  fclose(tmpFile);
  fclose(destFile);
}

void promptSave(void) {
  char filename[FILENAME_MAXLENGTH];
  prompt(PROMPT_SAVE, "%s", filename);

  saveBoardToFile(filename);
}

void restoreTempFile(char *filename) {
  FILE *tmpFile, *srcFile;
  srcFile = fopen(filename, "r");
  tmpFile = fopen(TEMPFILE_NAME, "w");

  char buffer;
  while ((buffer = fgetc(srcFile)) != EOF)
    fputc(buffer, tmpFile);

  fclose(tmpFile);
  fclose(srcFile);
}

void promptLoad(struct board *board) {
  char filename[FILENAME_MAXLENGTH];
  char boardString[SAVELEN + 1];
  FILE *file;
  int firstAttempt = 1;
  do {
    prompt(firstAttempt ? PROMPT_LOAD : PROMPT_LOAD_INVALID, "%s", filename);
    file = fopen(filename, "r");
    firstAttempt = 0;
  } while (!file);
  fseek(file, -SAVELEN - 1, SEEK_END);
  fgets(boardString, SAVELEN + 1, file);
  fclose(file);
  restoreTempFile(filename);
  loadBoard(boardString, board);
}
