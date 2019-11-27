#include "board.h"
#include "block.h"

vector<vector<Cell>>& Board::getBoard() {
    return myBoard;
}

void Board::move(string action, int i) {
    currBlock->move(action, i);
}