#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include "subject.h"
#include "blockinfo.h"
using namespace std;

class Cell;

class Board: public Subject<blockInfo> {
  vector<Cell> parts;
  blockInfo info;
  
  int width, height;
  int remaining = 4;  // ctor will take a value for remaining ie 1
  
 public:
  ~Board();
  
  bool move(int player, string action); // k i have no idea what the params r supposed to be what's the int
  void rotate(bool clockwise);
  void drop();
  void decreaseCells();
};

#endif
