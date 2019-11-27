#include <string>
#include <cstdlib>
#include "board.h"
#include "block.h"
#include "textdisplay.h"
#include "gdisplay.h"
#include "cell.h"
using namespace std;

Board::Board(int level = 0) : level{level} {}

void Board::levelChange(int newlevel) {
    level = newlevel;
}

void Board::move(string action, int i) {
    currBlock->move(action, i);
}

vector<vector<Cell>>& Board::getBoard() {
    return myBoard;
}
// should be called after drop
// takes currBlock and perma-adds it to the board & displays
// creates new block from nextBlock and sets it to curr
void Board::endTurn() {
    

    //using level probabilities, generate next block
    char newtype = generateNext(level);
    currBlock = new Block{newtype, level, myBoard};
}

char generateNext(int level) {
    if (level == 0) {
        //read in thing
    }
    else if (level == 1) {

    }
    else if (level == 2) {
        int type = (rand() % 7);
        if (type == 0) return 'I';
        if (type == 1) return 'O';
        if (type == 2) return 'T';
        if (type == 3) return 'J';
        if (type == 4) return 'L';
        if (type == 5) return 'S';
        if (type == 6) return 'Z';
    }
}


void Board::specialAction() {
    cout << "What special action (blind, heavy, force) would you like to select?" << endl;
    string s;
    cin >> s;
    if (s == "blind" || s == "Blind" || s == "BLIND")
        oppBoard->toggleBlind();
    else if (s == "heavy" || s == "Heavy" || s == "HEAVY")
        oppBoard->setHeavy();
    else if (s == "force" || s == "Force" || s == "FORCE") {
        char c;
        cin >> c;
        oppBoard->setNextBlock(c);
    }
}
void Board::toggleBlind() {
    isBlind = !isBlind;
}
void Board::setHeavy() {
    isHeavy = true;
}
void Board::setNextBlock(char newtype) {
    nextBlock = newtype;
}

bool Board::isRowFull(int rownum) {
    for (int i = 0; i < myBoard.at(0).size(); ++i) {
        if (!myBoard.at(rownum).at(i).getInfo().isFilled)
            return false;
    }
    return true;
}
void Board::clearRow(int rownum);

playerInfo Board::getInfo() {
    return {level, score, nextBlock};
};

void Board::notify(Subject<blockInfo> &whoNotified);
