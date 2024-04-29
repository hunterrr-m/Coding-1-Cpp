// Hunter McRight -- Coding 1
// Spring 2024 - Week 7, Day 2
// Functions continued: Recursive functions + Function overloading

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int Triple(int number) {
    return number * 3;
}

int DiceRoll(int sides = 6, int min = 1) {
    return rand() % sides + min;
}

string Triple(string input, bool vertical) {
    if(vertical) {
        string output;
        for(int i = 0; i < 3; i++) {
            output += input + "\n";
        }
        return output;
    } else {
        return input + input + input;
    }
}

// TESTING; trying to figure out recursive functions using the internet !!
// string Reverse(string &s) {
//     if(s.length() == 0) {
//         return "";
//     }

//     string last(1,s[s.length()-1]);
//     string reversed = Reverse(s.substr(0,s.length()-1));
//     return last+reversed;
// 

// string RecursiveReverse(string s, string prev = "") {
//     return (s.length() == 0 ? prev : RecursiveReverse(s.substr(0, s.length()-1), prev += s[s.length()]));
// }

// Recursive function that returns the input reversed.
string Recursive(string s) {
    // if empty, return it empty
    if (s.empty()) {
        return s;
    }
    // calling itself recursively, starting at the 2nd character, and moving the end
    // of the original string to the beginning of the resulting string until it
    // becomes empty.
    return Recursive(s.substr(1)) + s[0];
}

int AddRecursive(int n) {
    if(n == 0) {
        return 0;
    }
    return n + AddRecursive(n - 1);
}

int main() {
    srand(time(0));
    int number;
    string word;
    cout << "Enter a number: ";
    cin >> number;
    cout << "Tripled: " << Triple(number) << "\n";
    cout << "Recursive Addition: " << AddRecursive(number);
    cout << "\n====================\nEnter a word: ";
    cin >> word;
    cout << Triple(word, true);
    cout << Recursive(word) << "\n";
    cout << "====================\nYour d6 roll is: " << DiceRoll() << ".\n";
    cout << "Your d12 roll is: " << DiceRoll(12) << ".\n";
    cout << "Year born: " << DiceRoll(50, 1970);
}