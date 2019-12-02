#include "block.h"
using namespace std;

map<char,vector<vector<bool>>> Block::blockSettings = {
  {'O', {{true, true}, {true, true}}},
  {'J', {{true, false, false}, {true, true, true}}},
  {'I', {{true, true, true, true}}},
  {'Z', {{true, true, false}, {false, true, true}}},
  {'T', {{true, true, true}, {false, true, false}}},
  {'S', {{false, true, true}, {true, true, false}}},
  {'L', {{false, false, true}, {true, true, true}}}
};

// we chose to have the constructor interpret the type of block to create,
// as having a class for each block type would clutter up the file system
// while sharing the exact same methods for everything but the constructor.
Block::Block(char type, int level, int player, const vector<vector<Cell>> &gameBoard) : info{level, type, 3, 0} {    // each cells' parts vector is a vector of cells the size of the
    // smallest rectangle that encompasses the whole block. For example,
    // a 'Z' block has 6 cells in parts, with height 2 and width 3.
    // Then, parts[0] = parts [0 * height + width] is the top left cell,
    // and parts[6] similarly is the bottom right cell.

    // our starting "bottom left" position is always the same, in our design.
    // we have to "add 3" to each row index to accomodate for the 3 extra
    // rows above where the block would be created.
    board = gameBoard;

    vector<vector<bool>> setting = blockSettings[type]; //throw exception if invalid type entered

    height = setting.size();
    width = setting.at(0).size();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (setting[i][j]) {
                parts.emplace_back(Cell{i + 3, j, true, type, this, player});
            } else {
                parts.emplace_back(Cell{i + 3, j, false, type, this, player});
            } 
        }
    }
}

Block::~Block() { }

const vector<Cell> &Block::getParts() {
    return parts;
}

bool Block::checkOverlap() {
    // for each filled Cell in parts, we check if the cell in Board is taken
    for (Cell cell : parts) {
        if (cell.getInfo().isFilled && board.at(cell.getInfo().x).at(cell.getInfo().y).getInfo().isFilled) return true;
    }

    return false;
}


void Block::move(string action, int repeats) {

    // we repeat the move actions as many time as speicied by repeats
    for (int i = 0; i < repeats; ++i) {
        if (action == "left") {
            for (int j = 0; j < parts.size(); ++j) {
                cellInfo currInfo = parts.at(j).getInfo();

                // cannot move left any further
                if (currInfo.y == 0) {
                    return;
                }
                else if (currInfo.isFilled) {
                    // if the cell at position x,y is filled in our block object,
                    // make sure it's not filled in the cell we want to move to.
                    if (board.at(currInfo.x).at(currInfo.y - 1).getInfo().isFilled) {
                        return;
                    }
                }
            }
            --info.llx;
            for (Cell cell : parts) {
                cell.addToX(-1);
            }
        } else if (action == "right") {

            for (int j = 0; j < parts.size(); ++j) {
                    cellInfo currInfo = parts.at(j).getInfo();

                    // cannot move right any further
                    if (currInfo.y == 10) {
                        return;
                    }
                    else if (currInfo.isFilled) {
                        // if the cell at position x,y is filled in our block object,
                        // make sure it's not filled in the cell we want to move to.
                        if (board.at(currInfo.x).at(currInfo.y + 1).getInfo().isFilled) {
                            return;
                        }
                    }
            }
            ++info.llx;
            for (Cell cell : parts) {
                cell.addToX(1);
            }
        } else if (action == "down") {

            for (int j = 0; j < parts.size(); ++j) {
                cellInfo currInfo = parts.at(j).getInfo();

                // cannot move down any further
                if (currInfo.x == 17) {
                    return;
                }
                else if (currInfo.isFilled) {
                    // if the cell at position x,y is filled in our block object,
                    // make sure it's not filled in the cell we want to move to.
                    if (board.at(currInfo.x + 1).at(currInfo.y).getInfo().isFilled) {
                        return;
                    }
                }
            }
            ++info.lly;
            for (Cell cell : parts) {
                cell.addToY(-1);
            }
        } else if (action == "counterclockwise") {
            i %= 4;
            if (i != 4) rotate(4 - i);
        } else if (action == "clockwise") {
            i %= 4;
            if (i != 4) rotate(i);
        }
    }
}

void Block::rotate(int i) {
    cellInfo cInfo;

    for (int j = 0; j < i; ++j) {
        // we pretend to do the thing to check if there are conflicts
        for (Cell cell : parts) {
            cInfo = cell.getInfo();
            if (!board.at(cInfo.x + info.lly - cInfo.y).at(cInfo.y).getInfo().isFilled
                || !board.at(cInfo.x).at(cInfo.y + cInfo.x - info.llx - 2).getInfo().isFilled) return;
        }
        
        // we do the thing for real
        for (Cell cell : parts) {
            cInfo = cell.getInfo();

            cell.addToX(info.lly - cInfo.y);
            cell.addToY(cInfo.x - info.llx - 2);
        }

        int buf = width;
        width = height;
        height = buf;
    }
}

int Block::decreaseCells() {
    --remaining;
    
    if (remaining == 0) return (info.levelCreated + 1) * (info.levelCreated + 1);
    return 0;
}

blockInfo Block::getInfo() const {
    return info;
}
