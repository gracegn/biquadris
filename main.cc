#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "biquadris.h"
using namespace std;

int main(int argc, char *argv[]) {
    vector<string> commands = {
        "left", "right", "down", "clockwise", "counterclockwise",
        "drop", "levelup", "leveldown", "norandom", "random", "sequence",
        "I", "J", "L" , "T", "S", "O", "Z", "restart"
    };
    
    bool onlyText = false;
    int start_level = 0;
    int seed = 727;
    string scriptfile1 = "sequence1.txt";
    string scriptfile2 = "sequence2.txt";

    for (int i = 1; i < argc; ++i) {
        string arg(argv[i]);
        if (arg == "-text") {
            onlyText = true;
        }
        else if (arg == "-seed") {
            stringstream(argv[++i]) >> seed;
        }
        else if (arg == "-scriptfile1") {
            scriptfile1 = string(argv[++i]);
        }
        else if (arg == "-scriptfile2") {
            scriptfile2 = string(argv[++i]);
        }
        else if (arg == "-startlevel") {
            stringstream(argv[++i]) >> start_level;
        }
    }

    Biquadris game(start_level, seed, onlyText, scriptfile1, scriptfile2);
    game.boardsPrint();
    string input;
    int repeats;

    // we set buffers so that if we want to use command sequence,
    // we can switch reading from cin to reading from our file
    // and back again once it's empty.
    streambuf *filebuf, *cinbuf;
    cinbuf = cin.rdbuf();
    ifstream file;
    bool readFromFile = false;

    while(true) {
        cin >> input;

        // we need to check if we were reading a file or from CLI
        // to know whether to terminate the program or not
        if (cin.eof()) {
            if (readFromFile) {
                cin.rdbuf(cinbuf);
                file.close();
                readFromFile = false;
                continue;
            }
            else return 0;
        }
        
        stringstream sInput;
        sInput << "1" << input;
        sInput >> repeats;

        string temp = std::to_string(repeats);
        if (temp == "1")
            repeats = 1;
        else if (temp == "10")
            repeats = 0;
        else {
            repeats = stoi(temp.substr(1));
        }
        
        vector<string> buffer(commands);
        char read;
        int i = 0;

        while (sInput >> read) {

            for (int index = 0; index < buffer.size(); ++index) {
                if (read != buffer[index][i]) {
                    buffer.erase(buffer.begin() + index);
                    --index;
                }
            }

            if (buffer.size() == 1) {
                string c = buffer[0];
                // case town
                if (c == "left" || c == "down" || c == "right" 
                || c == "drop" || c == "clockwise" || c == "counterclockwise") {
                    game.move(c, repeats);
                }
                else if (c == "I" || c == "J" || c == "L" 
                || c == "T" || c == "S" || c == "Z" || c == "O") {
                    game.setCurrBlock(c.at(0));
                }
                else if (c == "levelup") {
                    game.levelChange(repeats);
                }
                else if (c == "leveldown") {
                    game.levelChange(-repeats);
                }
                else if (c == "norandom") {
                    string file;
                    cin >> file;
                    game.setNoRandom(file);
                }
                else if (c == "random") {
                    game.setRandom();
                }
                else if (c == "sequence") {
                    string fileName;
                    cin >> fileName; // reads file name
                    file.open(fileName);

                    // assign file's read buffer to filebuf
                    filebuf = file.rdbuf();
                    
                    // cin now reading from file's buffer
                    cin.rdbuf(filebuf);
                    readFromFile = true;
                }
                else if (c == "restart") {
                    game.restartGame();
                }
                cout << endl;
                game.boardsPrint();
                break;
            }
            else if (commands.size() == 0) {
                // nothing matched, uh oh moment
                cout << "uh oh moment" << endl;
                break;
            }
            else {
                ++i;
            }
        }

        int isGameOver = game.loserIs();
        if (isGameOver != 0) {
            cout << "G A M E O V E R" << endl;
            cout << "HIGHSCORE: " << game.getHighscore() << endl;

            if (isGameOver == 2) {
                cout << "WINNER: Player1\t\tLOSER: Player2" << endl;
            } else if (isGameOver == 1) {
                cout << "LOSER: Player1\t\tWINNER: Player2" << endl;
            }

            game.restartGame();
        }
    }
}