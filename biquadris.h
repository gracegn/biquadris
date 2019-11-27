#ifndef BIQUADRIS_H
#define BIQUADRIS_H
#include "playerinfo.h"
#include "board.h"
#include "textdisplay.h"
#include "gdisplay.h"
using namespace std;

class Biquadris {
  Board player1;
  Board player2;
  TextDisplay *td = nullptr;
  GraphicsDisplay *gd = nullptr;
  
  int turn = 1;
  int highscore = 0;
  int boardHeight, boardWidth;

 public:
  ~Biquadris();
  
  bool isGameOver() const;
  void newGame(int rows = 15, int cols = 11);
  void restartGame();
  void updateDisplays(playerInfo player1, playerInfo player2);
  bool move(int i, string action); // uhh idk what this returns and i guessed what the params meant, ask ericsons n jenn
  void boardsPrint(bool blind1, bool blind2);
};

#endif
