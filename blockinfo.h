#ifndef BLOCKINFO_H
#define BLOCKINFO_H

struct blockInfo {
  const int levelCreated;  // level # block was created
  // type of this block, type is one of {O,I,T,S,Z,L,J} for the respective
  // tetris block types, or ' ' for empty.
  const char type;  
  int llx, lly;  // x & y of the lower left corner
};

#endif
