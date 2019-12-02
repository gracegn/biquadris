#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "cell.h"
#include "observer.h"
#include "blockinfo.h"
#include "playerinfo.h"
#include "textdisplay.h"
#include "gdisplay.h"
using namespace std;

class Block;
// class InvalidMove{};

class Board : public Subject<playerInfo> {
  vector<vector<Cell>> myBoard;
  Board* oppBoard;
  int score = 0;
  // int seed;
  int level;
  string sequenceFile;
  vector<char> blockOrder;

  Block* currBlock;
  char nextBlock;

  bool isHeavy; // from opponent's special action
  bool isBlind;
  bool gameOver = false;

 public:
  ~Board();
  
  Board(int seed, int level, string scriptfile = "");
  void levelChange(int change);
  void move(string action, int i = 0);

  void endTurn();
  Block* createBlock();

  void specialAction();
  void toggleBlind();
  void setHeavy();
  void setNextBlock(char newtype);
  void setCurrBlock(char newtype);

  bool isRowFull(int rownum) const;
  int clearRow(int rownum);

  char generateNext(int level);
  vector<vector<Cell>> &getBoard();
  
  playerInfo getInfo() const;

  // void notify(Subject<blockInfo> &whoNotified) override;
};

#endif
