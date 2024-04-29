#include <iostream>
#include <string>
using std::cout;    // saves space vs. using entire std namespace file
using std::string;

void Hello() {
    cout << "Hello\n";
}

int triple(int num) {
    return num * 3;
}

string triple(string str) {
    return str + str + str;
}