#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "absdisplay.h"
//class Cell;

class TextDisplay: public AbsDisplay {
  std::vector<std::vector<char>> display1;
  std::vector<std::vector<char>> display2;
 public:
  TextDisplay(int rows, int cols);

  void notify(Subject<cellInfo> &whoNotified) override;
  void print(int player = 0);  // player = the one we add blind to, 0 means neither
  string TextDisplay::rowString(int player, int row, string blind = "");
};

#endif
