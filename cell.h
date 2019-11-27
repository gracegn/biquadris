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
  void swap(Cell &other);

  cellInfo getInfo();
  void setType(char toType);
  void addToX(int i);
  void addToY(int i);
  
  void clear();
};

#endif
