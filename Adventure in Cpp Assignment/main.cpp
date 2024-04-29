// Hunter McRight -- Coding 1
// Spring 2024 - Spring Break
// Adventure in C++ Assignment

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

// Rolls a number between 1-6
int RollDie(int sides = 6) {
    return rand() % sides + 1;
}

// Rolls a number between 1-20
int RollGold() {
    return rand() % 20 + 1;
}

// Asks the player if they would like to go adventuring.
string AskYesNo(string question = "n") {
    cout << "Would you like to go adventuring? (y/n) > ";
    cin >> question;
    if (question == "y") {
        return "y";
    } else if (question == "n") {
        return "n";
    } else {
        cout << "Please enter a valid response.\n";
        return "error";
    }
}

// Informs the user that they've died, returning "n" to stop the main loop
string Dead() {
    cout << "\x1B[31mYou died.\033[0m\n";
    return "n";
}

int main() {
    srand(time(0));
    string adventure = "y";
    int attack, block, gold;
    int totalGold = 0, turns = 0;
    int health = 10;
    bool alive = true;

    do {
        // display stats at the start of every turn
        cout << "Your stats are as follows:\n\x1B[31mHealth\033[0m: " << health << "\n\x1B[33mGold\033[0m: " << totalGold << "\n\n========================================\n\n";
        adventure = AskYesNo();
        // if 'y', go adventuring, if 'n', stop adventuring
        if (adventure == "y") {
            turns += 1;
            attack = RollDie();
            block = RollDie();
            cout << "While out on your adventure, an \x1B[32morc\033[0m attacks you!\n";
            sleep(1);
            cout << "The \x1B[32morc\033[0m attacks for " << attack << " point(s).\n";
            sleep(1);
            cout << "You block for " << block << " point(s).\n";
            sleep(1);
            // if block is greater than or equal to attack, you only lose 1 health and find between 1 and 20 gold.
            if (block >= attack) {
                health -= 1;
                if (health > 0) {
                    cout << "You successfully block the attack and got away safely! (\x1B[31m-1 health\033[0m)\n";
                    gold = RollGold();
                    totalGold = totalGold + gold;
                    sleep(1);
                    cout << "As you ran away, you stole " << gold << " \x1B[33mgold\033[0m.\n\n";
                    sleep(1);
                // in case the user successfully blocks, but only had 1 health
                } else {
                    sleep(1);
                    alive = false;
                    adventure = Dead();
                }
            // if block is less than attack, you lose however many points the orc attacked for, and find no gold
            } else if (block < attack) {
                health = health - attack;
                cout << "You failed to block the attack. (\x1B[31m-" << attack << " health\033[0m)\n";
                if (health > 0) {
                    sleep(1);
                    cout << "You were unable to find any \x1B[33mgold\033[0m.\n\n";
                    sleep(1);
                // in case the attack brings the players health to or below zero
                } else {
                    sleep(1);
                    alive = false;
                    adventure = Dead();
                }
            }
        // in case the player enters something other than 'y' or 'n'
        } else if (adventure == "error") {
            continue;
        }
    } while (adventure != "n");
    // if alive, displays turns lasted and total gold, along with a message if health is below 5
    if (alive) {
        cout << "You came back from your adventure alive!\n";
        if (health < 5) {
            sleep(1);
            cout << "You seem a little injured, you should visit the doctor.\n";
        }
        sleep(1);
        cout << "\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n";
        cout << "You lasted \033[36m" << turns << " turns\033[0m and found a total of \033[33m" << totalGold << " gold.\033[0m\n";
        cout << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/";
    // if dead, displays how much gold was left by their body
    } else {
        cout << "Unfortunately, you did not survive your adventure.\n";
        sleep(1);
        cout << "\x1B[33m" << totalGold << " gold \033[0mwas left by your body.";
    }
}