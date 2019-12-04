#ifndef GDISPLAY_H
#define GDISPLAY_H
#include "absdisplay.h"
#include "playerinfo.h"
#include "window.h"
#include <map>
class Cell;

class GraphicsDisplay: public AbsDisplay {
  Xwindow gdP1;
  Xwindow gdP2;
  Xwindow gdScore;
  playerInfo info1;
  playerInfo info2;
  bool justDropped1 = false;
  bool justDropped2 = false;

  std::map<char, std::vector<std::vector<bool>>> blockSettings;

  std::string defaultFont = "-adobe-helvetica-medium-r-normal--24-240-75-75-p-130-iso10646-1";
  std::string defaultSFont = "-adobe-helvetica-medium-r-normal--18-180-75-75-p-98-iso8859-1";

  int scoreHeight = 400; // width of scoreboard
  int scoreWidth = 200; // height of scoreboard
  int boardWidth = 11 * 30; // width of tetris board
  int boardHeight = 18 * 30; // height of board
  int boardBuffer = 5; // height of the separator between board and next block display
  int footerLength = 150; // height of next block display
  int ratio = 30;
  int p2LeftPadding = 500 / 2;

  void setup(playerInfo &info);
  void setupScore();

  void drawScore(playerInfo &info);
  void drawBlind(Xwindow &gd);
  void drawCoverNextBlock(playerInfo &info);
  void drawNextBlock(playerInfo &info);
  void drawCell(int x, int y, int colour, Xwindow &gd);
  void drawCoverBlock(playerInfo &info);
  void drawBlock(playerInfo &info);

 public:
  GraphicsDisplay(playerInfo info1, playerInfo info2, int rows, int cols, std::map<char, std::vector<std::vector<bool>>> blockSettings);

  void updateInfo(playerInfo info); // when level and scores change!!!
  void updateInfo(playerInfo player1, playerInfo player2);
  void notify(Subject<cellInfo> &whoNotified, Action type) override; // when next types change!!!
  void notify(Subject<playerInfo> &whoNotified, Action type) override;
  void addBlind(int player);
  void unBlind(std::vector<std::vector<Cell>>);  // the passed in cells are the ones we add back to the graphic display
};

#endif
