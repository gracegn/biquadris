#include "block.h"
using namespace std;


// we chose to have the constructor interpret the type of block to create,
// as having a class for each block type would clutter up the file system
// while sharing the exact same methods for everything but the constructor.
Block::Block(char type, int level, const vector<vector<Cell>> &gameBoard){

    // each cells' parts vector is a vector of cells the size of the
    // smallest rectangle that encompasses the whole block. For example,
    // a 'Z' block has 6 cells in parts, with height 2 and width 3.
    // Then, parts[0] = parts [0 * height + width] is the top left cell,
    // and parts[6] similarly is the bottom right cell.

    // our starting "bottom left" position is always the same, in our design.
    // we have to "add 3" to each row index to accomodate for the 3 extra
    // rows above where the block would be created.
    info = blockInfo{level, type, 3, 0};
    board = gameBoard;

    if (type == 'O') {
        height = 2;
        width = 2;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; i < width; ++i) {
                parts.emplace_back(Cell{{i+3,j,true,type}, this});
            }
        }
    }
    else if (type == 'I') {
        height = 1;
        width = 4;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; i < width; ++i) {
                parts.emplace_back(Cell{{i+3,j,true,type}, this});
            }
        }
    }
    else if (type == 'J') {
        height = 2;
        width = 3;

        parts.emplace_back(Cell{{0+3,0,true,type}, this});

        // cells [0,1] and [0,2] are unfilled cells, with no owner.
        parts.emplace_back(Cell{{0+3,1,false,'E'}, nullptr});
        parts.emplace_back(Cell{{0+3,2,false,'E'}, nullptr});

        parts.emplace_back(Cell{{1+3,0,true,type}, this});
        parts.emplace_back(Cell{{1+3,1,true,type}, this});
        parts.emplace_back(Cell{{1+3,2,true,type}, this});
    }
    else if (type == 'L') {
        height = 2;
        width = 3;

        // cells [0,0] and [0,1] are unfilled cells, with no owner.
        parts.emplace_back(Cell{{0+3,0,false,'E'}, nullptr});
        parts.emplace_back(Cell{{0+3,1,false,'E'}, nullptr});

        parts.emplace_back(Cell{{0+3,2,true,type}, this});
        parts.emplace_back(Cell{{1+3,0,true,type}, this});
        parts.emplace_back(Cell{{1+3,1,true,type}, this});
        parts.emplace_back(Cell{{1+3,2,true,type}, this});
    }
    else if (type == 'T') {
        height = 2;
        width = 3;


        parts.emplace_back(Cell{{0+3,0,true,type}, this});
        parts.emplace_back(Cell{{0+3,1,true,type}, this});
        parts.emplace_back(Cell{{0+3,2,true,type}, this});

        // cells [1,0] and [1,2] are unfilled cells, with no owner.
        parts.emplace_back(Cell{{1+3,0,false,'E'}, nullptr});
        parts.emplace_back(Cell{{1+3,1,true,type}, this});
        parts.emplace_back(Cell{{1+3,2,false,'E'}, nullptr});
    }
    else if (type == 'Z') {
        height = 2;
        width = 3;

        // we create unfilled cells similar to the pattern above

        parts.emplace_back(Cell{{0+3,0,true,type}, this});
        parts.emplace_back(Cell{{0+3,1,true,type}, this});
        parts.emplace_back(Cell{{0+3,2,false,'E'}, nullptr});

        parts.emplace_back(Cell{{1+3,0,false,'E'}, nullptr});
        parts.emplace_back(Cell{{1+3,1,true,type}, this});
        parts.emplace_back(Cell{{1+3,2,true,type}, this});
    }
    else if (type == 'S') {
        height = 2;
        width = 3;

        // we create unfilled cells similar to the pattern above

        parts.emplace_back(Cell{{0+3,0,false,'E'}, nullptr});
        parts.emplace_back(Cell{{0+3,1,true,type}, this});
        parts.emplace_back(Cell{{0+3,2,true,type}, this});

        parts.emplace_back(Cell{{1+3,0,true,type}, this});
        parts.emplace_back(Cell{{1+3,1,true,type}, this});
        parts.emplace_back(Cell{{1+3,2,false,'E'}, nullptr});
    }
    else {
        // throw an exception maybe
    }
}

void Block::move(string action, int repeats) {
    // later on, if we want to have combinations of moves, 
    // we would put this entire thing in a while loop

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
        }else if (action == "right") {

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
        repeats %= 4;
        if (i != 4) rotate(-i);
    } else if (action == "clockwise") {
        repeats %= 4;
        if (i != 4) rotate(i);
    }
    }
    
}
