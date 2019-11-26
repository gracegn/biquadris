#ifndef GDISPLAY_H
#define GDISPLAY_H
#include "absdisplay.h"
#include "window.h"
class Cell;

class GraphicsDisplay: public AbsDisplay {
  Xwindow theGDisplay;
 public:
  GraphicsDisplay(int width, int height);

  void notify(Subject<cellInfo> &whoNotified) override;
  void addBlind(int player);
  void unBlind(std::vector<std::vector<Cell>>);  // the passed in cells are the ones we add back to the graphic display
};

#endif
