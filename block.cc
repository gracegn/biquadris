#include "block.h"
using namespace std;

map<char,vector<vector<bool>>> Block::blockSettings = {
  {'O', {{true, true}, {true, true}}},
  {'J', {{true, false, false}, {true, true, true}}},
  {'I', {{false, false, false, false}, {true, true, true, true}}},
  {'Z', {{true, true, false}, {false, true, true}}},
  {'T', {{true, true, true}, {false, true, false}}},
  {'S', {{false, true, true}, {true, true, false}}},
  {'L', {{false, false, true}, {true, true, true}}}
};

// we chose to have the constructor interpret the type of block to create,
// as having a class for each block type would clutter up the file system
// while sharing the exact same methods for everything but the constructor.
Block::Block(char type, int level, int player, const vector<vector<Cell>> &gameBoard, int remaining) : info{level, type, 3, 0}, remaining{remaining} {    // each cells' parts vector is a vector of cells the size of the
    // smallest rectangle that encompasses the whole block. For example,
    // a 'Z' block has 6 cells in parts, with height 2 and width 3.
    // Then, parts[0] = parts [0 * height + width] is the top left cell,
    // and parts[6] similarly is the bottom right cell.

    // our starting "bottom left" position is always the same, in our design.
    // we have to "add 3" to each row index to accomodate for the 3 extra
    // rows above where the block would be created.
    board = gameBoard;

    // if it's a 1x1 level 4 block, do something special
    if (remaining == 1) {
        parts.emplace_back(Cell{3, 5, true, type, this, player});
        return;
    }

    vector<vector<bool>> setting = blockSettings[type]; //throw exception if invalid type entered

    height = setting.size();
    width = setting.at(0).size();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (setting[i][j]) {
                parts.emplace_back(Cell{i + 2, j, true, type, this, player});
            } else {
                parts.emplace_back(Cell{i + 2, j, false, type, this, player});
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


bool Block::move(string action, int repeats) {
    // we repeat the move actions as many time as specified by repeats

    bool anySuccess = false;
    if (action == "counterclockwise") {
        repeats %= 4;
        if (repeats != 4) anySuccess = rotate(4 - repeats);
    } else if (action == "clockwise") {
        repeats %= 4;
        if (repeats != 4) anySuccess = rotate(repeats);
    }

    for (int i = 0; i < repeats; ++i) {
        if (action == "left") {
            for (int j = 0; j < parts.size(); ++j) {
                cellInfo currInfo = parts.at(j).getInfo();

                // cannot move left any further
                if (currInfo.y == 0) {
                    return anySuccess;
                }
                else if (currInfo.isFilled) {
                    // if the cell at position x,y is filled in our block object,
                    // make sure it's not filled in the cell we want to move to.
                    if (board.at(currInfo.x).at(currInfo.y - 1).getInfo().isFilled) {
                        return anySuccess;
                    }
                }
            }
            anySuccess = true;
            --info.lly;
            for (int j = 0; j < parts.size(); ++j) {
                parts.at(j).addToY(-1);
            }
        } else if (action == "right") {

            for (int j = 0; j < parts.size(); ++j) {
                    cellInfo currInfo = parts.at(j).getInfo();

                    // cannot move right any further
                    if (currInfo.y == 10) {
                        return anySuccess;
                    }
                    else if (currInfo.isFilled) {
                        // if the cell at position x,y is filled in our block object,
                        // make sure it's not filled in the cell we want to move to.
                        if (board.at(currInfo.x).at(currInfo.y + 1).getInfo().isFilled) {
                            return anySuccess;
                        }
                    }
            }
            anySuccess = true;
            ++info.lly;
            for (int j = 0; j < parts.size(); ++j) {
                parts.at(j).addToY(1);
            }
        } else if (action == "down") {
            // check if we're allowed to move down, ie no board or blocked
            for (int j = 0; j < parts.size(); ++j) {
                cellInfo currInfo = parts.at(j).getInfo();

                // cannot move down any further
                if (currInfo.x == 17) {
                    return anySuccess;
                }
                else if (currInfo.isFilled) {
                    // if the cell at position x,y is filled in our block object,
                    // make sure it's not filled in the cell we want to move to.
                    if (board.at(currInfo.x + 1).at(currInfo.y).getInfo().isFilled) {
                        return anySuccess;
                    }
                }
            }
            anySuccess = true;
            ++info.llx;
            for (int j = 0; j < parts.size(); ++j) {
                parts.at(j).addToX(1);
            }
        }
    }
    return anySuccess;
}

bool Block::rotate(int i) {
    bool anySuccess = false;
    if (info.type == 'O') return anySuccess;

    for (int j = 0; j < i; ++j) {
        int offset;
        if (info.type == 'I') {
            if (rotateCycle == 2) {
                offset = 0;
            } else {
                offset = rotateCycle % 2 == 1 ? 3 : 1;
            }
        } else {
            offset = rotateCycle % 2 == 1 ? 2 : 1;
        }

        // we pretend to rotate, to check if there's space
        vector<Cell> testparts = parts;
        vector<Cell> bufparts = parts;
        for (int k = 0; k < width; ++k) {
            for (int m = 0; m < height; ++m) {    
                bool filled = testparts.at(k * height + m).getInfo().isFilled;
                testparts.at(k * height + m).setFilled(bufparts.at(width * (height - m - 1) + k).getInfo().isFilled);
                bufparts.at(width * (height - m - 1) + k).setFilled(filled);
            }
        }

        int bufHeight = width;
        int bufWidth = height;

        for (int k = 0; k < bufHeight; ++k) {
            for (int m = 0; m < bufWidth; ++m) {                           
                if (testparts.at(k * bufWidth + m).getInfo().isFilled
                && 
                (info.llx - bufHeight + 1 + k < 0
                || info.llx - bufHeight + 1 + k >= board.size()
                || info.lly - bufWidth + 1 + m + offset < 0
                || info.lly - bufWidth + 1 + m + offset >= board[0].size()
                || board.at(info.llx - bufHeight + 1 + k).at(info.lly - bufWidth + 1 + m + offset).getInfo().isFilled)) {
                    return anySuccess;
                }                                   

                testparts.at(k * bufWidth + m).setX(info.llx - bufHeight + 1 + k);
                testparts.at(k * bufWidth + m).setY(info.lly - bufWidth + 1 + m + offset);
            }
        }

        // checks passed, we assign to the actual parts the rotated parts
        parts = testparts;
        height = bufHeight;
        width = bufWidth;

        ++rotateCycle;
        rotateCycle %= 4;
        anySuccess = true;
    }
    return anySuccess;
}

int Block::decreaseCells() {
    --remaining;

    if (remaining == 0) return (info.levelCreated + 1) * (info.levelCreated + 1);
    return 0;
}

blockInfo Block::getInfo() const {
    return info;
}
