#ifndef GDISPLAY_H
#define GDISPLAY_H
#include "absdisplay.h"
#include "playerinfo.h"
#include "window.h"
class Cell;

class GraphicsDisplay: public AbsDisplay {
  Xwindow theGDisplay;
  playerInfo info1;
  playerInfo info2;
 public:
  GraphicsDisplay(playerInfo info1, playerInfo info2, int rows, int cols);

  void updateInfo(playerInfo player1, playerInfo player2); // when level and scores change!!!
  void notify(Subject<playerInfo> &whoNotified, Action type) override;
  void addBlind(int player);
  void unBlind(std::vector<std::vector<Cell>>);  // the passed in cells are the ones we add back to the graphic display
};

#endif
