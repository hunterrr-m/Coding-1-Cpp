#include "includes.h"

class robot {
public:
    int durability = 0;
    string name = "Unnamed";
    robot(int d = 0, string n = "Unnamed") {
        name = n;
        durability = d;
    }
};