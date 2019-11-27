#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "cellinfo.h"

class Block;

class Cell: public Subject<cellInfo> {
  
  int x, y;
  bool isFilled;
  char type;
  Block* owner;
  
 public:
  Cell(int x, int y, bool isFilled, char type, Block* owner);
  ~Cell();
  cellInfo getInfo() {
    return {x, y, isFilled, type};
  };
  
  void clear();
};

#endif
