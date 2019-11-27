#include <iostream>
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

void TextDisplay::notify(Subject<cellInfo> &whoNotified) {

}

// this is a 'helper' for Biquadris::boardsPrint
string TextDisplay::rowString(int player, int row, string blind = "") {
    string str = "";

    if (blind == "col") {
        for (int i = 0; i < cols; ++i) {
            if (3 <= i && i <= 9)
                str += "?";
            else {
                if (player == 1)
                    str += display1.at(row).at(i);
                else
                    str += display2.at(row).at(i);
            }
        }
    }

    else if (blind == "row") {
        for (int i = 0; i < cols; ++i)
            str += "?";
    }

    else {
        for (int i = 0; i < cols; ++i) {
            if (player == 1)
                str += display1.at(row).at(i);
            else
                str += display2.at(row).at(i);
        }
    }
    
    return str;
}

