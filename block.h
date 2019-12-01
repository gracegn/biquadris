#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include "subject.h"
#include "blockinfo.h"
#include "board.h"
#include "cell.h"

class Cell;

class Block: public Subject<blockInfo> {
  std::vector<Cell> parts;
  blockInfo info;
  std::vector<std::vector<Cell>> board;
  
  int width, height;
  int remaining = 4;  // ctor will take a value for remaining ie 1

  void rotate(int i);
 public:
  ~Block();
  
  Block(char type, int level, const std::vector<std::vector<Cell>> &gameBoard);
  const std::vector<Cell> &getParts();
  blockInfo getInfo() const override;
  
  void move(std::string action, int i = 0); // int is repetitions
  int decreaseCells();
};

#endif
