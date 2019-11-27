#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "cellinfo.h"

class Block;

class Cell: public Subject<cellInfo> {
  int x, y;
  bool isFilled; //??? or just enum
  char type; // 

  Block* owner;
  
 public:
  ~Cell();

  cellInfo getInfo();
  void setType(char toType);
  //void setXY(int newX, int newY); not convenient
  void addToX(int i);
  void addToY(int i);
  
  void clear();
};

#endif
