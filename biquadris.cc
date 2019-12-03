#include "biquadris.h"
using namespace std;

Biquadris::~Biquadris() {
    delete td;
    delete gd;
}
  
Biquadris::Biquadris(int start_level, int newseed, bool onlyText, string scriptfile1, string scriptfile2, int rows, int cols) : player1{Board(newseed, start_level, 1, scriptfile1)}, player2{Board(newseed, start_level, 2, scriptfile2)} {
    boardHeight = rows;
    boardWidth = cols;
    textOnly = onlyText;
    seed = newseed;

    td = new TextDisplay{rows, cols};
    player1.attach(td);
    player2.attach(td);

    if (!textOnly) {
        gd = new GraphicsDisplay{{start_level, 0, ' '}, {start_level, 0, ' '}, rows, cols};
        player1.attach(gd);
        player2.attach(gd);
    }

    player1.endTurn();
    player2.endTurn();
}

void Biquadris::restartGame() {
    delete td;
    td = new TextDisplay{boardHeight, boardWidth};
    if (!textOnly) {
        delete gd;
        gd = new GraphicsDisplay{player1.getInfo(), player2.getInfo(), boardHeight, boardWidth};
    }

    player1 = Board(seed, player1.getInfo().level, 1);
    player2 = Board(seed, player2.getInfo().level, 2);
    player1.attach(td);
    player2.attach(td);
    if (!textOnly) {
        player1.attach(gd);
        player2.attach(gd);
    }

    player1.endTurn();
    player2.endTurn();
    turn = 1;
}

// when level, score, or 'next' gets updated aka after every turn?
// DEAL WITH THIS LATER!!!!!! THIS ISN'T EVEN GETTING CALLED RN
void Biquadris::updateDisplays(playerInfo player1, playerInfo player2) {
    // td->updateInfo(player1, player2); idk if this is even necessary anymore bc text is updated here
    if (!textOnly) gd->updateInfo(player1, player2);
}

void Biquadris::setCurrBlock(char newType) {
    if (turn == 1) player1.setCurrBlock(newType);
    if (turn == 2) player2.setCurrBlock(newType);
} 


void Biquadris::move(string action, int repeats) {
    if (repeats == 0) return;
    if (action == "drop") { // for "drop" actions, we want to end the player's turn afterwards
        for (int i = 0; i < repeats; ++i) {
            if (turn == 1) {
                player1.move(action);
                if (highscore < player1.getInfo().score) highscore = player1.getInfo().score;
            } else {
                player2.move(action);
                if (highscore < player2.getInfo().score) highscore = player2.getInfo().score;
            }
        }
        toggleTurn();
    } else {
        turn == 1 ? player1.move(action, repeats) : player2.move(action, repeats);
    }
}

void Biquadris::levelChange(int change) {
    if (turn == 1) player1.levelChange(change);
    if (turn == 2) player2.levelChange(change);
}

// prints the textdisplays of both players side by side
// blind(i) refers to if player(i) is blind
// blind: columns 3-9 and rows 3-12
void Biquadris::boardsPrint() {
    bool blind1 = player1.getInfo().isBlind;
    bool blind2 = player2.getInfo().isBlind;

    string space = "\t\t";
    string sep = "-----------";
    cout << "Level:    " << player1.getInfo().level << space << "Level:    " << player2.getInfo().level << endl;
    cout << "Score:    " << player1.getInfo().score << space << "Score:    " << player2.getInfo().score << endl;
    cout << sep << space << sep << endl;
    
    
    for (int i = 0; i < boardHeight; ++i) {
        if (blind1) {
            if (3 <= i && i <= 12)
                cout << td->rowString(1, i, "row");
            else
                cout << td->rowString(1, i, "col");
        }
        else {
            cout << td->rowString(1, i);
        }

        cout << space;

        if (blind2) {
            if (3 <= i && i <= 12)
                cout << td->rowString(2, i, "row");
            else
                cout << td->rowString(2, i, "col");
        }
        else {
            cout << td->rowString(2, i);
        }

        cout << endl;
    }

    cout << sep << space << sep << endl;
    cout << "Next:      " << space << "Next:      " << endl;

    char block1 = player1.getInfo().nextBlock;
    vector<vector<bool>> setting1 = player1.getCurrBlock()->blockSettings[block1];
    char block2 = player2.getInfo().nextBlock;
    vector<vector<bool>> setting2 = player2.getCurrBlock()->blockSettings[block2];

    for (int j = 0; j < max(setting1.size(), setting2.size()); ++j) {
        if (setting1.size() > j) {
            for (int i = 0; i < setting1[0].size(); ++i) {
                setting1[j][i] ? cout << block1 : cout << ' ';
            }
        }

        cout << space << "\t";

        if (setting2.size() > j) {
            for (int i = 0; i < setting2[0].size(); ++i) {
                setting2[j][i] ? cout << block2 : cout << ' ';
            }
        }

        cout << endl;
    }

    //cout << player1.getInfo().nextBlock << space << "\t" << player2.getInfo().nextBlock << endl;
}

bool Biquadris::isGameOver() const {
    return (player1.getInfo().gameOver || player2.getInfo().gameOver);
}

void Biquadris::toggleTurn() {
    if (turn == 1) {
        turn = 0;
    } else {
        turn = 1;
    }
}