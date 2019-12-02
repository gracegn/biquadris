#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "absdisplay.h"
#include "cellinfo.h"
class Cell;

class TextDisplay: public AbsDisplay {
  std::vector<std::vector<char>> display1;
  std::vector<std::vector<char>> display2;

  std::vector<cellInfo> blockParts1;
  std::vector<cellInfo> blockParts2;
 public:
  TextDisplay(int rows, int cols);

  void notify(Subject<cellInfo> &whoNotified) override;
  void notify(Subject<playerInfo> &whoNotified) override;
  void print(int player = 0);  // player = the one we add blind to, 0 means neither
  std::string rowString(int player, int row, std::string blind = "");
  std::string rowStringH(std::vector<cellInfo> blockParts, std::vector<std::vector<char>> display, int row, std::string blind);
};

#endif
