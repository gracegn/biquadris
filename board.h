#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "observer.h"
#include "blockinfo.h"
using namespace std;

class Cell;
class Block;
// class InvalidMove{};

class Board: public Observer<blockInfo> {
  vector<vector<Cell>> myBoard;
  Board* oppBoard;
  int score = 0;
  int level = 0;

  Block* currBlock;
  char nextBlock;

  bool isHeavy;
  bool isBlind;

 public:
  ~Board();
  
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

  getInfo(); // who is calling this huh display?? idk what the return type should be, do i need to create 'boardinfo'??
  vector<vector<Cell>> &getBoard();

  void notify(Subject<blockInfo> &whoNotified) override;
};

#endif
