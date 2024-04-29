// Hunter McRight -- Coding 1
// Spring 2024 - Week 5
// Favorite Games Assignment

// Note: collapse and re-expand the current run if nothing shows in console

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//    finds if user input exactly matches a game in the list, then erases it
void removeGame(vector<string> &favGames, string match) {
    [[maybe_unused]] vector<string>::iterator iter;
    iter = find(favGames.begin(), favGames.end(), match);
    if(iter != favGames.end()) {
        favGames.erase(iter);
    }
}

int main() {
    vector<string> favGames;
    while(true) {
        string input = "";
        string replace = "";
        cout << "\n==================================\n\n";
        cout << "What would you like to do? (Add/Show/Remove/Quit) > ";
        cin >> input;
        //    converts all characters in the user's input to lowercase
        //    (so that the program runs regardless of casing)
        for (char &i : input) { 
            i = tolower(i); 
        }
        //    adds a game to the end of the vector
        if(input == "add") {
            cout << "What game would you like to add? > ";
            cin >> input;
            favGames.push_back(input);
            cout << "Game added.";
        //    shows the names and how many games in the vector
        } else if (input == "show") {
            cout << "So far, you have added " << favGames.size() << " favorite game(s).\n";
            for(int i = 0; i < favGames.size(); i += 1) {
                cout << "Game " << i + 1 << ": " << favGames[i] << "\n";
            }
        //    removes a selected game from the list
        } else if (input == "remove") {
            //    if there are no games, do not run 'remove'
            if(favGames.size() == 0) {
                cout << "No games to remove.\n";
            //    displays games currently in list / tries to find a game in the list
            //    that exactly matches user input. If there is a match, run removeGame().
            //    if there is not, alert the user that there is no game by that name.
            } else {
                for(int i = 0; i < favGames.size(); i += 1) {
                    cout << "Game " << i + 1 << ": " << favGames[i] << "\n";
                }
                cout << "What game would you like to remove?\n(Enter the exact name and casing)\n> ";
                cin >> input;
                if(find(favGames.begin(), favGames.end(), input) != favGames.end()) {
                    removeGame(favGames, input);
                    cout << input << " has been removed from your list.\n";
                } else {
                    cout << input << " is not in your games list.\n";
                }
            }
        //    returns 0 to exit the program.
        } else if (input == "quit") {
            cout << "Quitting...";
            return 0;
        //    alerts the user if they entered an invalid option.
        } else {
            cout << "Please enter a valid option.\n";
        }
    }
}