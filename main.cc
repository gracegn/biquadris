#include <iostream>
#include <string>
#include <sstream>
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

    while (cin >> input) {
        stringstream sInput;
        sInput << "0" << input;
        sInput >> repeats;
        if (repeats == 0) repeats = 1;

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

            // for (string com : buffer)
            //         cout << com << " ";
            //     cout << endl << endl;

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
                    // NOT IMPLEMENTED YET I THINK
                }
                else if (c == "random") {
                    // NOT IMPLEMENTED YET I THINK
                }
                else if (c == "sequence") {
                    cin >> input; // reads file name
                    // how do we read file
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

        if (game.isGameOver()) {
            return 0;
        }
    }
}