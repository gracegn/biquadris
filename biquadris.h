#ifndef BIQUADRIS_H
#define BIQUADRIS_H
#include "playerinfo.h"
#include "board.h"
#include "textdisplay.h"
#include "gdisplay.h"

class Biquadris {
  Board player1;
  Board player2;
  TextDisplay *td = nullptr;
  GraphicsDisplay *gd = nullptr;
  string scriptfile1;
  string scriptfile2;
  
  int turn = 1;
  int highscore = 0;
  int boardHeight, boardWidth;
  int seed;
  bool textOnly;

  void toggleTurn();

 public:
  Biquadris(int start_level, int newseed, bool textOnly, string scriptfile1, string scriptfile2, int rows = 18, int cols = 11); //  we just make newGame the constructor of biquadris
  ~Biquadris();

  int getHighscore() const;

  int loserIs() const;
  void restartGame();
  void updateDisplays(playerInfo player1, playerInfo player2);
  void move(string action, int repeats = 1);
  void levelChange(int change);
  void setRandom();
  void setNoRandom(string file);
  void setCurrBlock(char newType);
  void boardsPrint();
};

#endif
