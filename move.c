#include "move.h"
#include "dice.h"
#include "fame.h"
#include "menu.h"
#include "print.h"
#include "prompt.h"
#include "save.h"
#include "strings.h"
#include "structs.h"
#include <ncurses.h>

int checkWinner(struct board *board) {
  if ((*board).outside[0] == 15)
    return 0;
  else if ((*board).outside[1] == 15)
    return 1;
  else
    return -1;
}

int canRemovePiece(struct board *board, int source, int player) {
  if (!player) { // player 0
    if (source < (BOARD_SIZE * 3) / 4)
      return 0;
    for (int i = 0; i < (BOARD_SIZE * 3) / 4; i++)
      if ((*board).fields[i].player == 0 && (*board).fields[i].pieces > 0)
        return 0;
  } else { // player 1
    if (source > BOARD_SIZE / 4)
      return 0;
    for (int i = BOARD_SIZE; i >= BOARD_SIZE / 4; i--) {
      if ((*board).fields[i].player == 1 && (*board).fields[i].pieces > 0)
        return 0;
    }
  }

  return 1;
}

int hasPieceToRemove(struct board *board, int source, int destination,
                     int player) {
  if (!canRemovePiece(board, source, player))
    return 0;
  int diceResult = destination - source, start, direction;
  if (!player) {
    start = (BOARD_SIZE * 3) / 4;
    direction = 1;
  } else {
    diceResult *= -1; // for player 0, source < destination
    start = BOARD_SIZE / 4;
    direction = -1;
  }

  for (int i = start; i != start + (BOARD_SIZE / 4) * direction;
       i += direction) {
    if ((*board).fields[i].player == player && (*board).fields[i].pieces > 0 &&
        (i + diceResult * direction < 0 ||
         i + diceResult * direction >= BOARD_SIZE))
      return 1;
  }

  return 0;
}

int hasUnusedHit(struct board *board, int source, int destination, int player) {
  int diceResult = destination - source, start, direction;
  if (!player) {
    start = 0;
    direction = 1;
  } else {
    diceResult *= -1; // for player 0, source < destination
    start = BOARD_SIZE - 1;
    direction = -1;
  }
  int bestSource = -1;

  for(int i=start; i!=BOARD_SIZE-start-1; i+= direction) {
    if(
      ((*board).fields[i].player == player && (*board).fields[i].pieces > 0) &&
      ((*board).fields[i+(diceResult)*direction]).player != player && 
      (*board).fields[i+(diceResult)*direction].pieces == 1) {
      bestSource = i;
    } 
  }

  if(bestSource!=-1 && bestSource != source) return 1;
  else return 0;
}

int isLegalMove(struct board *board, int source, int destination, int player) {
  if (source < 0 || source >= BOARD_SIZE)
    return 0;

  if (hasUnusedHit(board, source, destination, player))
    return 0;

  if ((*board).fields[source].player != player)
    return 0;

  if (!(*board).fields[source].pieces)
    return 0;

  if (destination < 0 || destination >= BOARD_SIZE)
    return canRemovePiece(board, source, player);
  else if (hasPieceToRemove(board, source, destination, player))
    return 0;

  if ((*board).fields[destination].player != player &&
      (*board).fields[destination].pieces > 1)
    return 0;

  return 1;
}

void makeMove(struct board *board, int source, int destination) {
  if (destination <= -1 ||
      destination >= BOARD_SIZE) { // if we're removing a piece
    (*board).outside[(*board).fields[source].player]++;
  } else {
    if ((*board).fields[destination].player != (*board).fields[source].player &&
        (*board).fields[destination].pieces > 0 // if this is a hit
    ) {
      (*board).bar[(*board).fields[destination].player]++; // add to bar
    } else {
      // +1 piece to the field.
      // we don't do this in case of hit because there's already 1 piece there
      (*board).fields[destination].pieces++;
    }
    (*board).fields[destination].player = (*board).fields[source].player;
  }
  (*board).fields[source].pieces--;
}

void removeFromBar(struct board *board, int player, int diceResult) {
  int destination;
  if (player)
    destination = BOARD_SIZE - diceResult;
  else
    destination = diceResult - 1;

  if ((*board).fields[destination].player == player ||
      (*board).fields[destination].pieces <= 1) {
    if (!((*board).fields[destination].player != player &&
          (*board).fields[destination].pieces > 0)) {
      (*board)
          .fields[destination]
          .pieces++; // we don't add a piece in case of a hit.
    } else {
      (*board).bar[other(player)]++; // we do, however, add to the bar.
    }

    (*board).fields[destination].player = player;
    (*board).bar[player]--;
  }
}

void promptMove(struct board *board, int player, int diceResult) {
  int source, destination, firstMove = 1;
  if ((*board).bar[player] > 0) {
    removeFromBar(board, player, diceResult);
    return;
  }
  do {
    prompt(firstMove ? PROMPT_NEWMOVE : PROMPT_ILLEGAL_MOVE, "%d", &source);
    source -= 1; // backgammon fields are typically numbered from 1.
    destination = source + (diceResult * (player ? -1 : 1));
    firstMove = 0;
  } while (!(isLegalMove(board, source, destination, player)) && source != -1);
  if (source == -1)
    return; // skip move
  makeMove(board, source, destination);
}

int getPoints(struct board *board, int winner) {
  if ((*board).bar[other(winner)] > 0)
    return 3;

  if ((*board).outside[other(winner)] == 0)
    return 2;

  return 1;
}

void showResults(WINDOW *boardWindow, struct board *board, struct menu *menu,
                 int winner, int update) {
  if (update)
    (*board).won[winner] += getPoints(board, winner);
  mvwprintw(boardWindow, BOARD_WINDOW_HEIGHT / 2, BOARD_WINDOW_WIDTH / 6,
            WINNER_TEXT_FORMAT, winner + 1);
  wrefresh(boardWindow);
  if (update)
    updateFame((*board).won[winner]);
  loadMenu(menu, results);
}

void moveLoop(struct menu *menu, WINDOW *boardWindow, struct board *board) {
  int win;
  refresh();
  for (int i = 0; i < NUMBER_OF_DICE * 2; i++) {
    if ((*board).move.moves[i] == 0)
      continue;
    printDice((*board).move.moves, i % NUMBER_OF_DICE);
    promptMove(board, (*board).move.player, (*board).move.moves[i]);
    printBoard(boardWindow, board);
    if ((win = checkWinner(board)) != -1) {
      showResults(boardWindow, board, menu, win, 1);
      break;
    }
  }
  (*board).move.player = other((*board).move.player);
  rollDice((*board).move.moves);
  printPlayer((*board).move.player);
  printDice((*board).move.moves, -1);
  saveMoveToTemp(board);
}
