#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "absdisplay.h"
//class Cell;

class TextDisplay: public AbsDisplay {
  std::vector<std::vector<char>> theDisplay;
 public:
  TextDisplay(int width, int height);

  void notify(Subject<cellInfo> &whoNotified) override;
  void print(int player = 0);  // player = the one we add blind to, 0 means neither
};

#endif
