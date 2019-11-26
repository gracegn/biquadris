#ifndef CELLINFO_H
#define CELLINFO_H

//enum class Block { I, J, L, O, S, Z, T, none };

struct cellInfo {
  int x, y;
  bool isFilled; //??? or just enum
  char type; // or should this just be accessed from owner
};

#endif
