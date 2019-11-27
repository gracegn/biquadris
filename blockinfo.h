#ifndef BLOCKINFO_H
#define BLOCKINFO_H

struct blockInfo {
  const int levelCreated;  // level # block was created
  const char type; // chars I, J, L, O, S, Z, T refer to their respective
  // block types, and 'E' = empty
  int llx, lly;  // x & y of the lower left corner
};

#endif
