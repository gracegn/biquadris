#ifndef ABSDISPLAY_H
#define ABSDISPLAY_H
#include "observer.h"
#include "cellinfo.h"
#include "playerinfo.h"

class AbsDisplay: public Observer<cellInfo> {
  const int width;
  const int height;

  playerInfo player1;
  playerInfo player2;
  int highscore;

 public:
  // AbsDisplay(int width, int height); don't want a parent ctor, do we need?

  void notify(Subject<cellInfo> &whoNotified) = 0;
  void updateInfo(playerInfo player1, playerInfo player2);
};

#endif
