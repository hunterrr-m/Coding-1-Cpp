// Hunter McRight -- Coding 1
// Spring 2024 - Week 11
// Enemy Class Assignment
// Note: Continuing this is not required for the class, I personally have decided to try
// continuing this project for fun.
/*
Stuff that I'd like to add in the future:
    - Cleaner code (more comments, some stuff isn't used, etc.)
    - [THIRD PRIORITY] Elemental Damage (stronger / weaker against other elements).
    - Maybe adding gold as a 'score' to make it more competitive?
    - Bosses (?)
    - [FIRST PRIORITY] Only lasts 5 turns, plan to have it go on much longer (maybe forever).
    - [FIRST PRIORITY] More enemies, weapons, elements, consumables, etc.
    - [SECOND PRIORITY] Super unbalanced, would like to make it more balanced.
    - [SECOND PRIORITY] Enemy encounters and starting weapon are randomized, so it's
      very rng based rather than being more linear.
    - [FIRST PRIORITY] Only contains battles for now, hoping to add in-between 'exploration'
      segments where you can find loot, secrets, etc.
    - [FIRST PRIORITY] There are more turns than items available, meaning the last two
      turns you'll receive a broken 'error' item.
    - Durability is completely usused, probably getting rid of it unless tools
      actually become present in the game (might not need durability even then).
*/

#include "includes.h"
#include "globalVars.h"
#include "functions.h"
#include "classes.h"

class item {
public:
    itemType type = weapon;
    int damage = 0;
    int durability = 0;
    int healAmount = 0;
    string name = "Unnamed";
    elementalType element = normal;
    int itemIndex = 0;
    item(string n, itemType t, int d, elementalType e, int i) {
        name = n;
        type = t;
        damage = d;
        element = e;
        itemIndex = i;
    }
    // turning elementalType to a string to display
    string elementString(elementalType t) {
        switch(t){
            case normal: return "Normal";
                break;
            case ice: return "Ice";
                break;
            case poison: return "Poison";
                break;
            case steel: return "Steel";
                break;
            case water: return "Water";
                break;
            default: return "Unknown";
                break;
        }
    }
    // turning itemType to a string to display
    string itemTypeString(itemType t) {
        switch(t){
            case weapon: return "Weapon";
                break;
            case consumable: return "Consumable";
                break;
            default: return "Unknown";
                break;
        }
    }
    // usused; prints out item type, damage, and element of a weapon
    void Inspect() {
        cout << name << "\nItemType: [" << itemTypeString(type) << "]\nDamage: [" << damage << "]\nElement: [" << elementString(element) << "]\nDurability: [" << durability << "]\n";
    }
};

class enemy {
public:
    string name;
    int health;
    int enemyIndex;
    int weapon;
    enemy(string givenName = "-", int givenHealth = 1, int givenIndex = 0, int givenWeapon = 0) {
        name = givenName;
        health = givenHealth;
        enemyIndex = givenIndex;
        weapon = givenWeapon;
    }
};

// unused for now, may use for random events
int RollDie(int sides = 6) {
    return rand() % sides + 1;
}

// prints out all consumables currently collected
void CheckInventory(vector<int> InvIndex) {
    for(int i = 0; i < InvIndex.size(); i++) {
        switch(InvIndex[i]) {
            case 5: cout << "\n[" << InvIndex[i] << "] " << "\x1B[34mCup of Medicine\033[0m";
                break;
            case 6: cout << "\n[" << InvIndex[i] << "] " << "\x1B[34mSuspiciously Small Cup Holding Unknown Liquid\033[0m";
                break;
            case 7: cout << "\n[" << InvIndex[i] << "] " << "\x1B[34mCompletely Ordinary Empty Paper Cup\033[0m";
                break;
            case 8: cout << "\n[" << InvIndex[i] << "] " << "\x1B[34mArtistically Shaped and Colored Cup\033[0m";
                break;
            default: cout << "error";
                break;
        }
    }
}

// prints out all weapons currently collected
void CheckInventory(int InvIndex) {
    switch(InvIndex) {
        case 0: cout << "\n[Weapon] " << "\x1B[31mSteel Cup of Water (3 Water Damage)\033[0m";
            break;
        case 1: cout << "\n[Weapon] " << "\x1B[31mSlightly Larger and More Dense Steel Cup of Water (4 Steel Damage)\033[0m";
            break;
        case 2: cout << "\n[Weapon] " << "\x1B[31mFlimsy Paper Cup Half Full of Water (2 Normal Damage)\033[0m";
            break;
        case 3: cout << "\n[Weapon] " << "\x1B[31mOtherworldly Cup of Water Made From Unknown Materials (5 Poison Damage)\033[0m";
            break;
        case 4: cout << "\n[Weapon] " << "\x1B[31mFull Cup of Water With Ice Cubes (3 Ice Damage)\033[0m";
            break;
    }
}

int main() {
    srand(time(0));
    // good god that's a lot of variables
    string answer;
    bool turn = true;
    int pHealth = 30;
    int enemyHealth = 0;
    string enemyName = "Undefined";
    int enemyWeapon = 0;
    int useItem = 0;
    bool defense = false;
    int timer = 0;
    string weaponName = "Undefined";
    string element = "Undefined";
    int damage = 0;
    int itemDrop = 2;
    bool dead = false;
    bool draw = false;
    
    // title
    cout << "=== CUP WARS ===\n";
    sleep(1);
    cout << "Welcome to the super super rough version of Cup Wars!\n\n";
    sleep(3);

    // enemies
    enemy undefined = enemy("error", 0, 5, 0);
    enemy threatenCup = enemy("Slightly Threatening Cup", 8, 0, 2);
    enemy wiseCup = enemy("Wise Old Cup", 12, 1, 0);
    enemy cupBrute = enemy("Cup Brute", 15, 2, 1);
    enemy durableCup = enemy("Durable Cup", 25, 3, 4);
    enemy finalCup = enemy("Cup of Indescribable Horrors", 20, 4, 3);

    // weapons
    item steelCup = item("Steel Cup of Water", weapon, 3, water, 0);
    item bigSteelCup = item("Slightly Larger and More Dense Steel Cup of Water", weapon, 4, steel, 1);
    item paperCup = item("Flimsy Paper Cup Half Full of Water", weapon, 2, normal, 2);
    item otherworldCup = item("Otherworldly Cup of Water Made From Unknown Materials", weapon, 5, poison, 3);
    item iceCup = item("Full Cup of Water With Ice Cubes", weapon, 3, ice, 4);

    // consumables
    item medicine = item("Cup of Medicine", consumable, 0, normal, 5);
    item susCup = item("Suspiciously Small Cup Holding Unknown Liquid", consumable, 0, normal, 6);
    item emptyCup = item("Completely Ordinary Empty Paper Cup", consumable, 0, normal, 7);
    item artCup = item("Artistically Shaped and Colored Cup", consumable, 0, normal, 8);

    // assigns all items/enemies a number, then shuffles the array, providing random encounters / drops
    vector<int> weaponIndex = {0, 1, 2, 3, 4};
    vector<int> consumeIndex = {5, 6, 7, 8};
    vector<int> enemyIndex = {0, 1, 2, 3, 4};
    random_shuffle(weaponIndex.begin(), weaponIndex.end());
    random_shuffle(consumeIndex.begin(), consumeIndex.end());
    random_shuffle(enemyIndex.begin(), enemyIndex.end());
    vector<int> consumeObtained;
    int weaponObtained;

    // adds two random consumables to your inventory at the start of the game
    weaponObtained = weaponIndex[1];
    for(int i = 0; i < 2; i++) {
        consumeObtained.push_back(consumeIndex[i]);
    }

    // prints out inventory at the start of the game
    cout << "Here is your starting inventory:\n";
    CheckInventory(weaponObtained);
    CheckInventory(consumeObtained);
    sleep(1);
    
    int enemyTurn = 0;
    int currentEnemy = 0;
    
    string advAnswer;
    cout << "\n\nReady to adventure?\n(y/n) > ";
    cin >> advAnswer;
    if(advAnswer == "y") {
        // overall loop, runs as long as player has not completed all five turns or is killed.
        do {
            // adding +1 each turn so that you encounter a new enemy
            enemyTurn += 1;
            currentEnemy = enemyIndex[enemyTurn];
            // setting enemy health/name/weapon based on current enemy
            switch(currentEnemy) {
                case 0:
                    enemyHealth = threatenCup.health;
                    enemyName = threatenCup.name;
                    enemyWeapon = threatenCup.weapon;
                    break;
                case 1:
                    enemyHealth = wiseCup.health;
                    enemyName = wiseCup.name;
                    enemyWeapon = wiseCup.weapon;
                    break;
                case 2:
                    enemyHealth = cupBrute.health;
                    enemyName = cupBrute.name;
                    enemyWeapon = cupBrute.weapon;
                    break;
                case 3:
                    enemyHealth = durableCup.health;
                    enemyName = durableCup.name;
                    enemyWeapon = durableCup.weapon;
                    break;
                case 4:
                    enemyHealth = finalCup.health;
                    enemyName = finalCup.name;
                    enemyWeapon = finalCup.weapon;
                    break;
            }
            // setting enemy damage/element/weapon name based on enemy weapon
            switch(enemyWeapon) {
                case 0:
                    weaponName = steelCup.name;
                    element = steelCup.element;
                    damage = steelCup.damage;
                    break;
                case 1:
                    weaponName = bigSteelCup.name;
                    element = bigSteelCup.element;
                    damage = bigSteelCup.damage;
                    break;
                case 2:
                    weaponName = paperCup.name;
                    element = paperCup.element;
                    damage = paperCup.damage;
                    break;
                case 3:
                    weaponName = otherworldCup.name;
                    element = otherworldCup.element;
                    damage = otherworldCup.damage;
                    break;
                case 4:
                    weaponName = iceCup.name;
                    element = iceCup.element;
                    damage = iceCup.damage;
                    break;
            }
            sleep(1);
            cout << "As you walk along the path, you encounter " << enemyName << ".\n";

            // turn loop, runs as long as the enemy and player are both alive
            do {
                sleep(1);
                cout << "Your health: \x1B[33m" << pHealth << "\n\033[0mEnemy Health: \x1B[33m" << enemyHealth << "\n\033[0m";
                cout << "What will you do?\n(attack/item) > ";
                cin >> answer;
                cout << "\033c";
                // deals damage based on what weapon you got in the beginning
                if(answer == "attack") {
                    switch(weaponObtained) {
                        case 0: cout << "\nYou attack and deal \x1B[33m3\033[0m water damage.\n";
                            enemyHealth -= 3;
                            break;
                        case 1: cout << "\nYou attack and deal \x1B[33m4\033[0m steel damage.\n";
                            enemyHealth -= 4;
                            break;
                        case 2: cout << "\nYou attack and deal \x1B[33m2\033[0m normal damage.\n";
                            enemyHealth -= 2;
                            break;
                        case 3: cout << "\nYou attack and deal \x1B[33m5\033[0m poison damage.\n";
                            enemyHealth -= 5;
                            break;
                        case 4: cout << "\nYou attack and deal \x1B[33m3\033[0m ice damage.\n";
                            enemyHealth -= 3;
                            break;
                        default: cout << "error! line 290: if(attack) - switch(weaponObtained) [unknown weapon]\n";
                            break;
                    }
                    sleep(2);
                    // if enemy is killed, turn is over
                    if (enemyHealth <= 0) {
                        turn = false;
                    // else, enemy attacks
                    } else {
                        if (timer > 0) {
                            cout << enemyName << " is too mesmerized to attack!\n";
                            timer -= 1;
                        } else if (defense) {
                            cout << enemyName << " attacks using " << weaponName << ", dealing \x1B[33m" << damage-1 << "\033[0m damage!\n";
                            pHealth -= damage-1;
                        } else {
                            cout << enemyName << " attacks using " << weaponName << ", dealing \x1B[33m" << damage << "\033[0m damage!\n";
                            pHealth -= damage;
                        }
                    }
                    sleep(1);
                    // if player is killed, turn is over, game is over
                    if (pHealth <= 0) {
                        turn = false;
                        enemyTurn = 10;
                        dead = true;
                    }
                // displays your currently held consumables
                } else if (answer == "item") {
                    cout << "Your items:\n";
                    CheckInventory(consumeObtained);
                    cout << "\nWhich item would you like to use?\n> ";
                    cin >> useItem;
                    // checks if the players input is actually in their inventory
                    int cnt = count(consumeObtained.begin(), consumeObtained.end(), useItem);
                    sleep(1);
                    // if present in inventory, use item
                    if (cnt == 1) {
                        // finding what item the player has used
                        switch(useItem) {
                            // adds 15 health
                            case 5:
                                cout << "You drink the cup of medicine and gain \x1B[33m15\033[0m health!\n";
                                pHealth += 15;
                                break;
                            // adds 1 defense (-1 attack from all enemies)
                            case 6:
                                cout << "You drink the unknown liquid from the small cup. You now have \x1B[33m+1\033[0m defense point!\n";
                                defense = true;
                                break;
                            // does absolutely nothing lol
                            case 7:
                                cout << "You hold up the Completely Ordinary Empty Paper Cup.\n";
                                sleep(1);
                                cout << "...\n";
                                sleep(1);
                                cout << "Literally nothing happened.\n";
                                sleep(1);
                                break;
                            // makes it to where the enemy cannot attack for two turns
                            case 8:
                                cout << "You hold up the artistically shaped and colored cup.\n";
                                sleep(1);
                                cout << "The enemy is mesmerized by its beauty!\n";
                                timer = 3;
                                break;
                            default: cout << "error! line 346: switch(useItem) [unknown consumable]\n";
                                break;
                        }
                        sleep(2);
                        // if enemy is killed, turn is over
                        if (enemyHealth <= 0) {
                            turn = false;
                        // else, enemy attacks
                        } else {
                            if (timer > 0) {
                                cout << enemyName << " is too mesmerized to attack!\n";
                                timer -= 1;
                            } else if (defense) {
                                cout << enemyName << " attacks using " << weaponName << ", dealing \x1B[33m" << damage-1 << "\033[0m damage!\n";
                                pHealth -= damage-1;
                            } else {
                                cout << enemyName << " attacks using " << weaponName << ", dealing \x1B[33m" << damage << "\033[0m damage!\n";
                                pHealth -= damage;
                            }
                        }
                        // removes the item the player used from their inventory
                        consumeObtained.erase(remove(consumeObtained.begin(), consumeObtained.end(), useItem), consumeObtained.end());
                        // if player is dead, turn is over, game is over
                        if (pHealth <= 0) {
                            turn = false;
                            enemyTurn = 10;
                            dead = true;
                        }
                    // if item not present in inventory, throw error
                    } else {
                        cout << "Please enter a valid number!\n";
                    }
                // if something else is input besides 'attack' or 'item'
                } else {
                    cout << "Please enter a valid response!\n";
                }
                // if enemy is dead...
                if (enemyHealth <= 0) {
                    // if player is also dead, result in draw
                    if (pHealth <= 0) {
                        turn = false;
                        enemyTurn = 10;
                        dead = true;
                        draw = true;
                    // if player is alive, turn is over
                    } else {
                        turn = false;
                    }
                // if enemy is alive...
                } else {
                    // if player is dead, turn is over, game is over
                    if (pHealth <= 0) {
                        turn = false;
                        enemyTurn = 10;
                        dead = true;
                    // else, continue onto next turn
                    } else {
                        turn = true;
                    }
                }
            } while (turn);
            // if player is dead...
            if (dead) {
                // draw message
                if (draw) {
                    cout << "\033c";
                    cout << "You and " << enemyName << " have killed each other, resulting in a draw. Better luck next time!\n";
                // death message
                } else {
                    cout << "\033c";
                    cout << enemyName << " has killed you. Better luck next time!\n";
                }
            // if player is not dead, enemy slain message, player gains an item, onto next enemy
            } else {
                cout << "\033c";
                cout << enemyName << " was slain!\n";
                sleep(1);
                cout << enemyName << " dropped an item!\n";
                consumeObtained.push_back(consumeIndex[itemDrop]);
                itemDrop += 1;
            }
        } while (enemyTurn < 5);
        // if player is dead after turn five, do nothing (message already shown above)
        if (dead) {
            // do nothing
        // else, win message
        } else {
            cout << "\033c";
            cout << "Congratulations! You've successfully fought off all five enemies! Now go outside or something.";
        }
    // if player decides not to play
    } else {
        cout << "\033c";
        cout << "\nAlready leaving? That's a shame. :(";
    }
}