#include "gdisplay.h"
#include <string>

using namespace std;

GraphicsDisplay::GraphicsDisplay(playerInfo info1, playerInfo info2, int rows, int cols, map<char, vector<vector<bool>>> blockSettings) : AbsDisplay{rows, cols}, info1{info1}, info2{info2}, blockSettings{blockSettings}, gdP1{11 * 30, 18 * 30 + 150}, gdP2{11 * 30, 18 * 30 + 150}, gdScore{200, 400} { //fix the gd init later
    setup(info1);
    setup(info2);
    setupScore();
}

void GraphicsDisplay::setupScore() {
    gdScore.fillRectangle(0, 0, scoreWidth, scoreHeight, Xwindow::Black);

    gdScore.drawStringFont(ratio, ratio * 2, "Player 1", defaultFont, Xwindow::White);
    gdScore.drawStringFont(ratio, ratio * 3, "Level: " + to_string(info1.level), defaultSFont, Xwindow::White);
    gdScore.drawStringFont(ratio, ratio * 4, "Score: " + to_string(info1.score), defaultSFont, Xwindow::White);

    gdScore.drawStringFont(ratio, scoreHeight / 2, "Player 2", defaultFont, Xwindow::White);
    gdScore.drawStringFont(ratio, scoreHeight / 2 + ratio * 2, "Level: " + to_string(info2.level), defaultSFont, Xwindow::White);
    gdScore.drawStringFont(ratio, scoreHeight / 2 + ratio * 3, "Score: " + to_string(info2.score), defaultSFont, Xwindow::White);
}

void GraphicsDisplay::drawScore(playerInfo &info) {
    if (info.player == 1) {
        gdScore.fillRectangle(ratio, ratio * 3.2, scoreWidth, ratio, Xwindow::Black);
        gdScore.drawStringFont(ratio, ratio * 4, "Score: " + to_string(info.score), defaultSFont, Xwindow::White);
    } else {
        gdScore.fillRectangle(ratio, scoreHeight / 2 + ratio * 2.2, scoreWidth, ratio, Xwindow::Black);
        gdScore.drawStringFont(ratio, scoreHeight / 2 + ratio * 3, "Score: " + to_string(info.score), defaultSFont, Xwindow::White);
    }
}

void GraphicsDisplay::setup(playerInfo &info) {
    if (info.player == 1) {
        gdP1.fillRectangle(0, 0, boardWidth, boardHeight + footerLength, Xwindow::Black);
        gdP1.fillRectangle(0, boardHeight, boardHeight, boardBuffer, Xwindow::White);

        gdP1.drawStringFont(ratio, boardHeight + boardBuffer + ratio, "Next:", defaultFont, Xwindow::White);
    } else {
        gdP2.fillRectangle(0, 0, boardWidth, boardHeight + footerLength, Xwindow::Black);
        gdP2.fillRectangle(0, boardHeight, boardHeight, 5, Xwindow::White);

        gdP2.drawStringFont(ratio, boardHeight + boardBuffer + ratio, "Next:", defaultFont, Xwindow::White);
    }

    updateInfo(info);
    drawNextBlock(info);
    drawBlock(info);
}

int getColourFromType(char type) {
    if (type == 'O') {
        return Xwindow::Red;
    } else if (type == 'J') {
        return Xwindow::Green;
    } else if (type == 'I') {
        return Xwindow::Cyan;
    } else if (type == 'Z') {
        return Xwindow::Yellow;
    } else if (type == 'T') {  
        return Xwindow::Magenta;
    } else if (type == 'S') {
        return Xwindow::Orange;
    } else if (type == 'L') {
        return Xwindow::Blue;
    } else {
        return Xwindow::Black;
    }
}

void GraphicsDisplay::drawCoverNextBlock(playerInfo &info) {
    char block = info.nextBlock;
    vector<vector<bool>> setting = blockSettings[block];

    if (info.player == 1) {
        for (int i = 0; i < setting.size(); ++i) {
            for (int j = 0; j < setting.at(0).size(); ++j) {
                gdP1.fillRectangle(ratio * (j + 1), boardHeight + boardBuffer + ratio * (i + 2), ratio, ratio, Xwindow::Black);
            }
        }
    } else {
        for (int i = 0; i < setting.size(); ++i) {
            for (int j = 0; j < setting.at(0).size(); ++j) {
                gdP2.fillRectangle(ratio * (j + 1), boardHeight + boardBuffer + ratio * (i + 2), ratio, ratio, Xwindow::Black);
            }
        }
    }
}

void GraphicsDisplay::drawNextBlock(playerInfo &info) {
    int colour = getColourFromType(info.nextBlock);
    char block = info.nextBlock;
    vector<vector<bool>> setting = blockSettings[block];

    if (info.player == 1) {
        for (int i = 0; i < setting.size(); ++i) {
            for (int j = 0; j < setting.at(0).size(); ++j) {
                if (setting.at(i).at(j)) {
                    gdP1.fillRectangle(ratio * (j + 1), boardHeight + boardBuffer + ratio * (i + 2), ratio, ratio, colour);
                } else {
                    gdP1.fillRectangle(ratio * (j + 1), boardHeight + boardBuffer + ratio * (i + 2), ratio, ratio, Xwindow::Black);
                }
            }
        }
    } else {
        for (int i = 0; i < setting.size(); ++i) {
            for (int j = 0; j < setting.at(0).size(); ++j) {
                if (setting.at(i).at(j)) {
                    gdP2.fillRectangle(ratio * (j + 1), boardHeight + boardBuffer + ratio * (i + 2), ratio, ratio, colour);
                } else {
                    gdP2.fillRectangle(ratio * (j + 1), boardHeight + boardBuffer + ratio * (i + 2), ratio, ratio, Xwindow::Black);
                }
            }
        }
    }
}

void GraphicsDisplay::drawCoverBlock(playerInfo &info) {
    for (cellInfo cInfo : info.parts) {
        if (cInfo.isFilled) drawCell(cInfo.x, cInfo.y, Xwindow::Black, (info.player == 1 ? gdP1 : gdP2));
    }
}

void GraphicsDisplay::drawBlock(playerInfo &info) {
    for (cellInfo cInfo : info.parts) {
        if (cInfo.isFilled) drawCell(cInfo.x, cInfo.y, getColourFromType(cInfo.type), (info.player == 1 ? gdP1 : gdP2));
    }
}

void GraphicsDisplay::drawCell(int x, int y, int colour, Xwindow &gd) {
    gd.fillRectangle(ratio * y, ratio * x, ratio, ratio, colour);
}

void GraphicsDisplay::drawBlind(Xwindow &gd) {
    gd.fillRectangle(0, ratio * 5, ratio * 11, ratio * 10, Xwindow::Brown); // rows 3-12
    gd.fillRectangle(ratio * 2, ratio * 3, ratio * 7, ratio * 15, Xwindow::Brown); //cols 3-9
}

void GraphicsDisplay::notify(Subject<cellInfo> &whoNotified, Action type) {
    //unused
}
void GraphicsDisplay::notify(Subject<playerInfo> &whoNotified, Action type) {
    playerInfo info = whoNotified.getInfo();

    if (type == Action::BlockChange) {
        // draw bbb
        if (info.isBlind) info.player == 1 ? drawBlind(gdP1) : drawBlind(gdP2);
    
        if (info.player == 1 ? !justDropped1 : !justDropped2) {
            drawCoverBlock((info.player == 1 ? info1 : info2));
        }

        drawScore(info);

        info.player == 1 ? justDropped1 = false : justDropped2 = false;
        drawBlock(info);
        drawNextBlock(info);
    } else if (type == Action::BlockDrop) {
        if ((info.player == 1 && info1.isBlind) || (info.player == 2 && info2.isBlind)) {
            // redraw everything under bbb or juST REDRAW EVERYTHING
            for (vector<cellInfo> row : info.board) {
                for (cellInfo cInfo : row) {
                    if (cInfo.isFilled) {
                        drawCell(cInfo.x, cInfo.y, getColourFromType(cInfo.type), (info.player == 1 ? gdP1 : gdP2));
                    } else {
                        drawCell(cInfo.x, cInfo.y, Xwindow::Black, (info.player == 1 ? gdP1 : gdP2));
                    }
                }
            }
        }

        drawCoverBlock((info.player == 1 ? info1 : info2));
        drawBlock(info);
        drawCoverNextBlock((info.player == 1 ? info1 : info2));
        info.player == 1 ? justDropped1 = true : justDropped2 = true;
    } else if (type == Action::ClearRow) {
        // redraw everything
        for (vector<cellInfo> row : info.board) {
            for (cellInfo cInfo : row) {
                if (cInfo.isFilled) {
                    drawCell(cInfo.x, cInfo.y, getColourFromType(cInfo.type), (info.player == 1 ? gdP1 : gdP2));
                } else {
                    drawCell(cInfo.x, cInfo.y, Xwindow::Black, (info.player == 1 ? gdP1 : gdP2));
                }
            }
        }
    }

    updateInfo(info);
}

void GraphicsDisplay::updateInfo(playerInfo player1, playerInfo player2) {
    info1 = player1;
    info2 = player2;
}

void GraphicsDisplay::updateInfo(playerInfo info) {
    info.player == 1 ? info1 = info : info2 = info;
}

