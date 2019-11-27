#ifndef BLOCKINFO_H
#define BLOCKINFO_H

struct blockInfo {
  const int levelCreated;  // level # block was created
  const char type;  // type of this block
  int llx, lly;  // x & y of the lower left corner
};

#endif
