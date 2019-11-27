#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include "subject.h"
#include "blockinfo.h"
#include "board.h"
using namespace std;

class Cell;

class Block: public Subject<blockInfo> {
  vector<Cell> parts;
  Board* board;
  blockInfo info;
  
  int width, height;
  int remaining = 4;  // ctor will take a value for remaining ie 1

  void rotate(int i);
 public:
  ~Block();
  
  void move(string action, int i = 0);
  //void drop(); // handled in move function
  void decreaseCells();
};

#endif
