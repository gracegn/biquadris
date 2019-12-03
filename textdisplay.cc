#include <iostream>
#include "cellinfo.h"
#include "cell.h"
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(int rows, int cols) : AbsDisplay{rows, cols} {
    // initialise with ' ' in every spot
    for (int i = 1; i <= rows; ++i) {
        vector<char> row;
        for (int j = 0; j < cols; ++j) row.emplace_back(' ');

        display1.emplace_back(row);
        display2.emplace_back(row);
    }
}

// unused thus far
void TextDisplay::notify(Subject<cellInfo> &whoNotified, Action type) {
    cout << "td notified in cellinfo" << endl;
    cellInfo info = whoNotified.getInfo();
    if (info.isFilled && info.player == 1) {
        display1[info.x][info.y] = info.type;
    } else {
        display1[info.x][info.y] = ' ';
    }
    if (info.isFilled && info.player == 2) {
        display2[info.x][info.y] = info.type;
    } else {
        display2[info.x][info.y] = ' ';
    }
}

void TextDisplay::notify(Subject<playerInfo> &whoNotified, Action type) {
    if (type == Action::BlockChange) {
        playerInfo info = whoNotified.getInfo();
        if (info.player == 1)
            blockParts1 = whoNotified.getInfo().parts;
        if (info.player == 2)
            blockParts2 = whoNotified.getInfo().parts;
    }
    
    if (type == Action::BlockDrop) {
        for (cellInfo info : whoNotified.getInfo().parts) {
            if (info.isFilled) {
                if (info.player == 1)   display1[info.x][info.y] = info.type;
                if (info.player == 2)   display2[info.x][info.y] = info.type;
            }
        }
    }

    if (type == Action::ClearRow) {
        for (vector<cellInfo> row : whoNotified.getInfo().board) {
            for (cellInfo info : row) {
                if (info.player == 1)   display1[info.x][info.y] = info.type;
                if (info.player == 2)   display2[info.x][info.y] = info.type;
            }
        }
    }
}

// this is a 'helper' for Biquadris::boardsPrint
string TextDisplay::rowString(int player, int row, string blind) {
    if (player == 1) return rowStringH(blockParts1, display1, row, blind);
    if (player == 2) return rowStringH(blockParts2, display2, row, blind);
    return "error";
}
string TextDisplay::rowStringH(vector<cellInfo> blockParts, vector<vector<char>> display, int row, string blind) {
    string str = "";

    // for (auto info: blockParts) {
    //     cout << "x=" << info.x << ",y=" << info.y << endl;
    // }

    if (blind == "col") {
        for (int i = 0; i < cols; ++i) {
            if (3 <= i && i <= 9)
                str += "?";
            else {
                bool currBlockOn = false;
                for (auto info: blockParts) {
                    if (info.isFilled) {
                        if (info.x == row && info.y == i) {
                            str += info.type;
                            currBlockOn = true;
                        }
                    }
                }
                if (!currBlockOn) str += display.at(row).at(i);
            }
        }
    }

    else if (blind == "row") {
        for (int i = 0; i < cols; ++i)
            str += "?";
    }

    else {
        for (int i = 0; i < cols; ++i) {
            bool currBlockOn = false;
            for (auto info: blockParts) {
                if (info.isFilled) {
                    if (info.x == row && info.y == i) {
                        str += info.type;
                        currBlockOn = true;
                    }
                }
            }
            if (!currBlockOn) str += display.at(row).at(i);
        }
    }
    
    return str;
}

