#include "gdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(playerInfo info1, playerInfo info2, int rows, int cols) : AbsDisplay{rows, cols}, info1{info1}, info2{info2} {
    // FIGURE OUT THE SIZING AND STUFF!!!
    theGDisplay.fillRectangle(0, 0, 500, 500, Xwindow::White);
}

void GraphicsDisplay::updateInfo(playerInfo player1, playerInfo player2) {
    info1 = player1;
    info2 = player2;
}
