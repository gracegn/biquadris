#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include <map>
#include "subject.h"
#include "blockinfo.h"
#include "board.h"
#include "cell.h"

class Cell;

class Block {
  std::vector<Cell> parts;
  blockInfo info;

  std::vector<std::vector<Cell>> board;
  
  int width, height;
  int remaining;  // ctor will take a value for remaining ie 1

  int rotateCycle = 0;

  bool rotate(int i);
 public:
  ~Block();
  Block(char type, int level, int player, const std::vector<std::vector<Cell>> &gameBoard, int remaining = 4);

  static std::map<char, std::vector<std::vector<bool>>> blockSettings;
  
  const std::vector<Cell> &getParts();
  blockInfo getInfo() const;
  bool checkOverlap();
  
  bool move(std::string action, int repeats = 0); // int is repetitions
  int decreaseCells();
};

#endif
