#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "cellinfo.h"
#include "block.h"

class Block;

class Cell: public Subject<cellInfo> {
  int x, y;
  bool isFilled;
  char type;
  Block* owner;
  int player;
  
 public:
  Cell(int x, int y, bool isFilled, char type, Block* owner, int player);

  cellInfo getInfo() const override;
  Block* getOwner();
  void setType(char toType);
  void addToX(int i);
  void addToY(int i);
  
  void clear();
};

#endif
