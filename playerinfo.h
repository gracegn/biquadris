#ifndef PLAYERINFO_H
#define PLAYERINFO_H

struct playerInfo {
  int level;  // level # the player selected
  int score;  // current player score
  char nextBlock;  // type of next block
  bool gameOver;
  bool isBlind;
};

#endif
