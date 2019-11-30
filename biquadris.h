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

  void toggleTurn();

 public:
  ~Biquadris();
  
  bool isGameOver() const;
  void newGame(int rows = 15, int cols = 11);
  void restartGame();
  void updateDisplays(playerInfo player1, playerInfo player2);
  void move(string action, int repeats = 1); // uhh idk what this returns and i guessed what the params meant, ask ericsons n jenn
  void boardsPrint(bool blind1, bool blind2);
};

#endif
