#include "biquadris.h"
using namespace std;

Biquadris::~Biquadris() {
    delete td;
    delete gd;
}
  
//   bool Biquadris::isGameOver() const;
void Biquadris::newGame(int rows = 15, int cols = 11) {
    boardHeight = rows;
    boardWidth = cols;
    td = new TextDisplay{rows, cols};
    gd = new GraphicsDisplay{rows, cols};
    
    player1 = Board(*td, *gd);
    player2 = Board(*td, *gd);
}

void Biquadris::restartGame() {
    delete td;
    td = new TextDisplay{boardHeight, boardWidth};
    delete gd;
    gd = new GraphicsDisplay{boardHeight, boardWidth};

    player1 = Board(*td, *gd);
    player2 = Board(*td, *gd);
    turn = 1;
    // editing the highscore should be in the function that updates score
}

// when level, score, or 'next' gets updated aka after every turn?
void Biquadris::updateDisplays(playerInfo player1, playerInfo player2) {
    td->updateInfo(player1, player2);
    gd->updateInfo(player1, player2);
}

bool Biquadris::move(int i, string action) { // uhh idk what this returns and i guessed what the params meant, ask ericsons n jenn
    if (action == "drop" || action == "somefuturecommand") { // no clue what this means either lol how can it equal two things huh
        
    } else {
        turn == 1 ? player1.move(i, action) : player2.move(i, action);
    }
}

// prints the textdisplays of both players side by side
// blind(i) refers to if player(i) is blind
// blind: columns 3-9 and rows 3-12
void Biquadris::boardsPrint(bool blind1, bool blind2) {
    string space = "\t\t\t";
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
    }

    cout << sep << space << sep << endl;
    cout << "Next:      " << space << "Next:      " << endl;
    // next output
}

