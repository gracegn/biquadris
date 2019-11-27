#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "observer.h"
#include "blockinfo.h"
#include "playerinfo.h"
using namespace std;

class Cell;
class Block;
// class InvalidMove{};

class Board: public Observer<blockInfo> {
  vector<vector<Cell>> myBoard;
  Board* oppBoard;
  int score = 0;
  int level;

  Block* currBlock;
  char nextBlock;

  bool isHeavy;
  bool isBlind;

 public:
  ~Board();
  
  Board(const TextDisplay &td, const GraphicsDisplay &gd, int level = 0);
  // should it take in pointer in order for us to attach stuff??? but we want const right idk
  void levelChange(int newlevel);
  bool move(int player, string action); // again same as in biquadris, ask eircnsi and jenn
  void rotate(int times, char direction); // i thought that the move function gets rid of the need for rotate n drop n stuff in board???  
  void drop();

  Block* createBlock();

  void specialAction();
  void toggleBlind();
  void increaseHeavy();
  void setNextBlock(char newtype);

  void setCurrBlock(char newtype);

  void endTurn();   // what the heck is this for
  bool isRowFull(int rownum);
  void clearRow(int rownum);

  vector<vector<Cell>> &getBoard();
  playerInfo getInfo() {
    return {level, score, nextBlock};
  };

  void notify(Subject<blockInfo> &whoNotified) override;
};

#endif
