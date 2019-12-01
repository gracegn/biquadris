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

    Biquadris game(start_level, seed, onlyText);
    game.boardsPrint();
    // game.newGame(start_level, seed, onlyText);
    string input;
    int repeats = 1;

    while (cin >> input) {
        
        stringstream sInput(input);

        vector<string> buffer(commands);
        // int size = buffer.size();
        char read;
        int i = 0;
        stringstream sInput(input);

        while (sInput >> read) {
            int delIndex = 0;
            for (string com : commands) {
                if (read != com[i]) {
                    buffer.erase(buffer.begin() + delIndex);
                }
                else {
                    ++delIndex;
                }
            }
            if (commands.size() == 1) {
                string c = commands[0];
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
                    game.levelChange(1);
                }
                else if (c == "leveldown") {
                    game.levelChange(-1);
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
                game.boardsPrint();
            }
            else if (commands.size() == 0) {
                // nothing matched, uh oh moment
                cout << "uh oh moment" << endl;
            }
        }

        if (game.isGameOver()) {
            return 0;
        }
        repeats = 1;
    }
}