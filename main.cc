#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "biquadris.h"
using namespace std;

int main(){
    vector<string> commands = 
        {"left", "right", "down", "clockwise", "counterclockwise",
        "drop", "levelup", "leveldown", "norandom", "random", "sequence",
        "I", "J", "L" , "T", "S", "O", "Z", "restart"};
    
    Biquadris game;
    game.newGame();
    string input;
    int repeats = 1;

    while (cin >> repeats >> input) {
        vector<string> buffer = commands;
        int size = buffer.size();
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
                    // NOT IMPLEMENTED YET I THINK
                }
                else if (c == "levelup") {
                    // NOT IMPLEMENTED YET I THINK
                }
                else if (c == "leveldown") {
                    // NOT IMPLEMENTED YET I THINK
                }
                else if (c == "norandom") {
                    // NOT IMPLEMENTED YET I THINK
                }
                else if (c == "random") {
                    // NOT IMPLEMENTED YET I THINK
                }
                else if (c == "sequence") {
                    // NOT IMPLEMENTED YET I THINK
                }
                else if (c == "restart") {
                    game.restartGame();
                }
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