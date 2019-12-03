#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include <vector>
#include "cellinfo.h"

struct playerInfo {
  int player; // 1 or 2
  int level;  // level # the player selected
  int score;  // current player score
  char nextBlock;  // type of next block
  bool gameOver;
  bool isBlind;
  std::vector<cellInfo> parts;
  std::vector<std::vector<cellInfo>> board;
};

#endif
