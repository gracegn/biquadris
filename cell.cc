#include "cell.h"

cellInfo Cell::getInfo() {
    return cellInfo {x, y, isFilled, type};
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