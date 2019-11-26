#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "cellinfo.h"

class Block;

class Cell: public Subject<cellInfo> {
  
  cellInfo info;
  Block* owner;
  
 public:
  ~Cell();
  
  void clear();
};

#endif
