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

  bool isHeavy; // from opponent's special action
  bool isBlind;

 public:
  ~Board();
  
  Board(int level = 0);
  void levelChange(int newlevel);
  bool move(int player, string action);

  void endTurn();
  Block* createBlock();

  void specialAction();
  void toggleBlind();
  void setHeavy();
  void setNextBlock(char newtype);

  bool isRowFull(int rownum);
  void clearRow(int rownum);

  playerInfo getInfo();

  void notify(Subject<blockInfo> &whoNotified) override;
};

#endif
