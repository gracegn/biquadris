#ifndef BIQUADRIS_H
#define BIQUADRIS_H
#include "cellinfo.h"
#include "playerinfo.h"
#include "board.h"
using namespace std;

class Cell;
class Board;
class TextDisplay;
class GraphicsDisplay;
template <typename InfoType> class Observer;
// class InvalidMove{};

class Biquadris {
  Board player1;
  Board player2;
  TextDisplay *td = nullptr;
  GraphicsDisplay *gd = nullptr;
  
  // Add private members, if necessary.
  int turn = 1;
  int highscore = 0;
  int boardHeight;
  int boardWidth;

 public:
  ~Biquadris();
  
  bool isGameOver() const;
  void newGame(int rows = 15, int cols = 11);
  void restartGame();
  void updateDisplays(playerInfo player1, playerInfo player2);
  bool move(int player, string action); // uhh idk what this returns and i guessed what the params meant, ask ericsons n jenn
};

#endif
