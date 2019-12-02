#include <string>
#include <cstdlib>
#include <cmath> // for squaring, are we allowed??
#include <fstream>
#include "board.h"
#include "block.h"
#include "textdisplay.h"
#include "gdisplay.h"
#include "cell.h"
using namespace std;

Board::Board(int seed, int level, int player, string scriptFile) : level{level} {
    srand(seed); // i have no idea where this is supposed to go, hopefully here lol
    if (scriptFile != "") sequenceFile = scriptFile;

    if (level == 0) {
        fstream sequence;
        sequence.open(sequenceFile);
        char block;
        while (sequence >> block) {
            blockOrder.emplace_back(block);
        }
    }

    nextBlock = blockOrder.at(0);
    blockOrder.erase(blockOrder.begin());

    for (int i = 0; i < height; ++i) {
        vector<Cell> tempvec;
        for (int j = 0; j < width; ++j) {
            tempvec.emplace_back(Cell{i, j, false, 'E', nullptr, player});
        }
        myBoard.emplace_back(tempvec);
    }

    endTurn(); // to set up the first blocks
}

Board::~Board() {
    delete currBlock;
}

void Board::levelChange(int change) {
    level += change;
    if (level < 0) level = 0;
    if (level > 4) level = 4;
}

void Board::move(string action, int i) {
    if (action == "drop") {
        //drop is special, since we actually make permanent changes to the board.
        currBlock->move("down", 15);

        // here we "lock" the block to the board.
        vector<Cell> parts = currBlock->getParts();
        for (auto cell : parts) {
            cellInfo info = cell.getInfo();
            if (info.isFilled) {
                // assign our block's cell to this cell.
                myBoard.at(info.x).at(info.y) = cell;
            }
        }

        int numRowsCleared = 0;
        int blocksErasedScore = 0;
        for (int i = 0; i < 18; ++i) {
            if (isRowFull(i)) {
                blocksErasedScore += clearRow(i);
                ++numRowsCleared;
            }
        }
        score += pow(level + numRowsCleared, 2) + blocksErasedScore; // highscore is updated in biquadris
        endTurn();
    }
    else {
        currBlock->move(action, i);
    }
}

vector<vector<Cell>>& Board::getBoard() {
    return myBoard;
}
// should be called after drop
// takes currBlock and perma-adds it to the board & displays
// creates new block from nextBlock and sets it to curr
// and generates a new nextBlock
// don't have to return score as biquadris accesses & checks through getInfo()
void Board::endTurn() {
    currBlock = new Block{nextBlock, level, player, myBoard};
    if (currBlock->checkOverlap()) {
        gameOver = true;
    }

    nextBlock = generateNext(level);
    notifyObservers();
}

char Board::generateNext(int level) {
    if (level == 0) {
        if (blockOrder.empty()) {
            fstream sequence;
            sequence.open(sequenceFile);
            char block;
            while (sequence >> block) {
                blockOrder.emplace_back(block);
            }
        }
        else {
            char block = blockOrder.front();
            blockOrder.erase(blockOrder.begin());
            return block;
        }
    }
    else if (level == 1) {
        int type = (rand() % 12);
        if (type == 0) return 'S';
        if (type == 1) return 'Z';
        if (type == 2 || type == 3) return 'T';
        if (type == 4 || type == 5) return 'J';
        if (type == 6 || type == 7) return 'L';
        if (type == 8 || type == 9) return 'I';
        if (type == 10 || type == 11) return 'O';
    }
    else if (level == 2) {
        int type = (rand() % 7);
        if (type == 0) return 'S';
        if (type == 1) return 'Z';
        if (type == 2) return 'T';
        if (type == 3) return 'J';
        if (type == 4) return 'L';
        if (type == 5) return 'I';
        if (type == 6) return 'O';
    }
    else if (level == 3 || level == 4) {
        int type = (rand() % 9);
        if (type == 0 || type == 1) return 'S';
        if (type == 2 || type == 3) return 'Z';
        if (type == 4) return 'T';
        if (type == 5) return 'J';
        if (type == 6) return 'L';
        if (type == 7) return 'I';
        if (type == 8) return 'O';
    }
    return '0';
}


void Board::specialAction() {
    cout << "What special action (blind, heavy, force) would you like to select?" << endl;
    string s;
    cin >> s;
    if (s == "blind" || s == "Blind" || s == "BLIND" || s == "b" || s == "B")
        oppBoard->toggleBlind();
    else if (s == "heavy" || s == "Heavy" || s == "HEAVY" || s == "h" || s == "H")
        oppBoard->setHeavy();
    else if (s == "force" || s == "Force" || s == "FORCE" || s == "f" || s == "F") {
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
void Board::setCurrBlock(char newtype) {
    delete currBlock;
    currBlock = new Block{newtype, level, player, myBoard};
}

bool Board::isRowFull(int rownum) const {
    for (int i = 0; i < myBoard.at(0).size(); ++i) {
        if (!myBoard.at(rownum).at(i).getInfo().isFilled)
            return false;
    }
    return true;
}

// returns score of any blocks erased
int Board::clearRow(int rownum) {
    // remove row from cells vector
    myBoard.erase(myBoard.begin() + rownum);

    int blockScore = 0;
    
    // edit cell info - decrement each cell's coordinate
    // call cell's owner block to decrease cells
    for (int i = rownum; i < myBoard.size(); ++i) {
        for (Cell cell : myBoard[i]) {
            cell.addToX(-1);
            blockScore += cell.getOwner()->decreaseCells();
        }
    }

    return blockScore;
}

Block* Board::getCurrBlock() {return currBlock; }

playerInfo Board::getInfo() const {
    return {level, score, nextBlock, gameOver, isBlind};
};

// void Board::notify(Subject<blockInfo> &whoNotified) {

// }
