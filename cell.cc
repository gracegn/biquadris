#include "cell.h"

Cell::Cell(int x, int y, bool isFilled, char type, Block* owner, int player) : x{x}, y{y}, isFilled{isFilled}, type{type}, owner{owner}, player{player} {}

cellInfo Cell::getInfo() const {
    return cellInfo {x, y, isFilled, type, player};
}

Block* Cell::getOwner() {
    return owner;
}

void Cell::setType(char toType) {
    type = toType;
}

void Cell::addToX(int i) {
    x += i;
}

void Cell::addToY(int i) {
    y += i;
}
