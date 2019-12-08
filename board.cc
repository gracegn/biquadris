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

Board::Board(int seed, int level, int player, string scriptFile) : player{player}, level{level}, sequenceFile{scriptFile} {
    srand(seed); // i have no idea where this is supposed to go, hopefully here lol

    nextBlock = generateNext(level);

    for (int i = 0; i < height; ++i) {
        vector<Cell> tempvec;
        for (int j = 0; j < width; ++j) {
            tempvec.emplace_back(Cell{i, j, false, ' ', nullptr, player});
        }
        myBoard.emplace_back(tempvec);
    }
}

void Board::levelChange(int change) {
    level += change;
    if (level < 0) level = 0;
    if (level > 4) level = 4;
}

bool Board::move(string action, int repeats) {
    // only for "heavy" debuff
    bool shouldDrop = false;

    if (action == "drop") {
        //if blind, remove it
        if (isBlind) {
            toggleBlind();
            notifyObservers(Action::RemoveBlind);
        }

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
        notifyObservers(Action::BlockDrop);


        int numRowsCleared = 0;
        int blocksErasedScore = 0;
        for (int row = 0; row < 18; ++row) {
            if (isRowFull(row)) {
                blocksErasedScore += clearRow(row);
                ++numRowsCleared;
            }
        }
        // highscore is updated in biquadris
        if (numRowsCleared != 0)
            score += pow(level + numRowsCleared, 2);
        score += blocksErasedScore;

        // drop the level 4 center block
        if (level == 4 && parts.size() != 1) {
            ++blocksDropped;

            if (numRowsCleared != 0) {
                blocksDropped = 0;
            } else if (blocksDropped == 5) {
                blocksDropped = 0;
                dropCenterBlock();
            } 
        }

        if (numRowsCleared > 1) endTurn(true);
        else endTurn();
    }
    else {
        bool success = currBlock->move(action, repeats);
        if (success) {
            if (level == 3 || level == 4) currBlock->move("down", 1);
            if (isHeavy && (action == "right" || action == "left")) {
                // we move downwards twice, but are particularly interested if the second
                // move registers. If it doesn't, we drop.
                currBlock->move("down", 1);
                bool canMove = currBlock->move("down", 1);
                if (!canMove) {
                    // tell board to drop
                    shouldDrop = true;
                }
            }
        }
        notifyObservers();
    }
    return shouldDrop;
}

void Board::dropCenterBlock() {
    delete currBlock;
    currBlock = new Block{'*', level, player, myBoard, 1};
    if (currBlock->checkOverlap()) {
        gameOver = true;
    } else {
        move("drop");
        notifyObservers();
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
void Board::endTurn(bool special) {
    currBlock = new Block{nextBlock, level, player, myBoard};
    if (currBlock->checkOverlap()) {
        gameOver = true;
    } else {
        nextBlock = generateNext(level);
        notifyObservers();
    }

    if (special) specialAction();
}

char Board::generateNext(int level) {
    if (!isRand) {
        if (noRandOrder.empty()) {
            fstream sequence;
            sequence.open(noRandFile);
            char block;
            while (sequence >> block) {
                noRandOrder.emplace_back(block);
            }
        }
        char block = noRandOrder.front();
        noRandOrder.erase(noRandOrder.begin());
        return block;
    }
    else if (level == 0) {
        if (blockOrder.empty()) {
            fstream sequence;
            sequence.open(sequenceFile);
            char block;
            while (sequence >> block) {
                blockOrder.emplace_back(block);
            }
        }
        char block = blockOrder.front();
        blockOrder.erase(blockOrder.begin());
        return block;
    }
    else if (level == 1) {
        cout << "in level 1" << endl;
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
    if (s == "blind" || s == "Blind" || s == "BLIND" || s == "b" || s == "B") {
        oppBoard->toggleBlind();
        notifyObservers(Action::Blind);
    }
    else if (s == "heavy" || s == "Heavy" || s == "HEAVY" || s == "h" || s == "H") {
        oppBoard->setHeavy();
    }
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
    notifyObservers();
}
void Board::setCurrBlock(char newtype) {
    delete currBlock;
    currBlock = new Block{newtype, level, player, myBoard};
    notifyObservers();
}

void Board::setNoRand(string file) {
    isRand = false;
    noRandFile = file;
    noRandOrder.clear();

    fstream sequence;
    sequence.open(file);
    char block;

    while (sequence >> block) {
        noRandOrder.emplace_back(block);
    }
}

void Board::setRand() {
    isRand = true;
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
    // cout << "clearing row " << rownum << endl;
    int blockScore = 0;

    for (int i = 0; i <= rownum; ++i) {
        for (int j = 0; j < myBoard.at(i).size(); ++j) {
            Cell* curr = &myBoard.at(i).at(j);
            // if (i == rownum && curr->getInfo().isFilled) {
            if (i == rownum && curr->getInfo().type != ' ') {
                // cout << "row=" << i << ", cell=" << j << endl;
                Block* owner = curr->getOwner();
                // cout << "got owner" << endl;
                int incScore = owner->decreaseCells();
                // cout << "incScore " << incScore << endl;
                if (incScore != 0) {
                    // cout << "about to delete" << endl;
                    delete curr->getOwner();
                    // cout << "done deleting" << endl;
                    blockScore += incScore;
                }
            }
            else {
                curr->addToX(1);
            }
        }
    }
    // cout << "blockScore = " << blockScore << endl;

    // remove row from cells vector and add empty row to top
    myBoard.erase(myBoard.begin() + rownum);
    
    vector<Cell> newrow;
    for (int i = 0; i < myBoard.at(0).size(); ++i)
        newrow.emplace_back(Cell{0, i, false, ' ', nullptr, player});
    myBoard.insert(myBoard.begin(), newrow);

    notifyObservers(Action::ClearRow);
    return blockScore;
}

Block* Board::getCurrBlock() {return currBlock; }

void Board::setOppBoard(Board* opponentBoard) {
    oppBoard = opponentBoard;
}

playerInfo Board::getInfo() const {
    vector<Cell> parts = currBlock->getParts();
    vector<cellInfo> partsInfo;
    for (auto cell : parts) {
        partsInfo.emplace_back(cell.getInfo());
    }

    vector<vector<cellInfo>> boardInfo;
    for(auto row : myBoard) {
        vector<cellInfo> temprow;
        for (auto cell : row) {
            temprow.emplace_back(cell.getInfo());
        }
        boardInfo.emplace_back(temprow);
    }

    return {player, level, score, nextBlock, gameOver, isBlind, partsInfo, boardInfo};
};

void Board::printBoard() {
    for (int i = 0; i < myBoard.size(); ++i) {
        for (int j = 0; j < myBoard.at(i).size(); ++j) {
            cout << myBoard.at(i).at(j).getInfo().type;
        }
        cout << endl;
    }
    cout << endl;
}

Board::~Board() {
    delete currBlock;
    for (int i = 0; i < myBoard.size(); ++i) {
        for (int j = 0; j < myBoard.at(i).size(); ++j) {
            Cell* curr = &myBoard.at(i).at(j);
            if (curr->getInfo().isFilled){
                if (curr->getOwner()->decreaseCells() != 0) //score
                    delete curr->getOwner();
            }
        }
    }
}
