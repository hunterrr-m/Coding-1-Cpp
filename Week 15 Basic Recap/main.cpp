// Hunter McRight -- Coding 1
// Spring 2024 - Week 15, Day 1
// Recap!

#include "includes.h"
#include "functions.h"
#include "classes.h"
using namespace std;

class weapon {
public:
    string name = "defaultWeapon";
    int damage = 5;

    // default constructor
    weapon() : name("debug"), damage(1) {}

    weapon(string givenName, int givenDamage) {
        name = givenName;
        damage = givenDamage;
    }
};

class human {
public:
    string name;
    // assigning a weapon to a human
    weapon heldWeapon;

    human(string givenName, weapon givenWeapon) {
        name = givenName;
        heldWeapon = givenWeapon;
    }
};

int main() {
    //weapon debugWeapon("debug", 1);
    weapon kusarigama("Kusarigama", 20);
    human humanOne("Lukas", kusarigama);

    cout << "Memory address of kusarigama is " << &kusarigama << ".\n";
}