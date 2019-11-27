#include "block.h"
#include "cell.h"

void Block::move(string action, int i) {
    // later on, if we want to have combinations of moves, we would put this entire thing in a while loop

    if (action == "drop") {
        move("down", 15);
    } else if (action == "left") {
        info.llx -= i;
        for (Cell cell : parts) {
            cell.addToX(-i);
        }
    } else if (action == "right") {
        info.llx += i;
        for (Cell cell : parts) {
            cell.addToX(i);
        }
    } else if (action == "down") {
        info.lly += i;
        for (Cell cell : parts) {
            cell.addToY(i);
        }
    } else if (action == "counterclockwise") {
        i %= 4;
        if (i != 4) rotate(4 - i);
    } else if (action == "clockwise") {
        i %= 4;
        if (i != 4) rotate(i);
    }
}

void Block::rotate(int i) {
    cellInfo cInfo;
    vector<vector<Cell>> myBoard = board->getBoard();

    for (int j = 0; j < i; ++j) {
        // we pretend to do the thing to check if there are conflicts
        for (Cell cell : parts) {
            cInfo = cell.getInfo();
            if (!myBoard.at(cInfo.x + info.lly - cInfo.y).at(cInfo.y).getInfo().isFilled
                || !myBoard.at(cInfo.x).at(cInfo.y + cInfo.x - info.llx - 2).getInfo().isFilled) return;
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