#pragma once

struct board;

#define TEMPFILE_NAME "gammontmp"
#define FILENAME_MAXLENGTH 100
#define SAVELEN 59

void loadBoard(const char *bString, struct board *dest);

void serializeBoard(struct board *board, char *destination);

void clearTemp(void);

void saveMoveToTemp(struct board *board);

void saveBoardToFile(char *path);

void promptSave(void);

void restoreTempFile(char *filename);

void promptLoad(struct board *board);
