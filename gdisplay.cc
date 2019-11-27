#include "gdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int rows, int cols) : AbsDisplay{rows, cols} {
    // FIGURE OUT THE SIZING AND STUFF!!!
    theGDisplay.fillRectangle(0, 0, 500, 500, Xwindow::White);
}