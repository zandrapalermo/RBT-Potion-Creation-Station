#include "Potion.h"
#include "RedBlackTree.h"
#include <iostream>
#include <limits>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Helper function to get validated int input
int getIntInput(const string& prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value < minVal || value > maxVal) {
                cout << "Value must be between " << minVal << " and " << maxVal << ". Try again.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Helper function to get validated string input
string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    while (input.empty()) {
        cout << "Input cannot be empty! Try again: ";
        getline(cin, input);
    }
    return input;
}

int main() {
    vector<Potion> potions; // store all potions
    function<int(const Potion &)> sortFunc;

    auto selectSorting = [&]() {
        cout << "Welcome to The Potion Creation Station!\n";
        cout << "To get started, please select a potion sorting method:\n";
        cout << "1. Total Stats\n";
        cout << "2. Strength\n";
        cout << "3. Speed\n";
        cout << "4. Health\n";
        cout << "Please select your choice!: ";

        int choice = getIntInput("", 1, 4);

        switch (choice) {
        case 2:
            sortFunc = [](const Potion &p) { return p.strength; };
            break;
        case 3:
            sortFunc = [](const Potion &p) { return p.speed; };
            break;
        case 4:
            sortFunc = [](const Potion &p) { return p.health; };
            break;
        default:
            sortFunc = [](const Potion &p) { return p.totalStats(); };
            break;
        }
    };

    // Initial sorting selection
    selectSorting();

    // Create tree with selected sort key
    RedBlackTree tree(sortFunc);
    for (const auto &p : potions)
        tree.insert(p);

    cout << "Now onto the Potion Main Menu....\n";
    while (true) {
        cout << "\n--- Menu ---\n";
        cout << "\n(Helpful Tip: Choose option 6 if you want to sort your potions differently!)\n";
        cout << "1. Add Potion\n";
        cout << "2. Display All Potions \n";
        cout << "3. Search Potion by Name\n";
        cout << "4. Delete Potion by Name\n";
        cout << "5. Clear All Potions\n";
        cout << "6. Change Sorting Method\n";
        cout << "7. Quit\n";
        cout << "Please select your choice!: ";

        int menuChoice = getIntInput("", 1, 7);

        if (menuChoice == 1) {
            string name = getStringInput("Potion name: ");
            int str = getIntInput("Strength: ", 0, 100000);
            int spd = getIntInput("Speed: ", 0, 100000);
            int hp = getIntInput("Health: ", 0, 100000);

            Potion p(name, str, spd, hp);
            potions.push_back(p);
            tree.insert(p);
            cout << "Potion added!\n";
        }
        else if (menuChoice == 2) {
            if (potions.empty()) {
                cout << "You have no potions in your inventory to be displayed!\n";
            } else {
                cout << "\n=== Potion List ===\n";
                tree.inorder(true);
            }
        }
        else if (menuChoice == 3) {
            if (potions.empty()){
                cout << "You have no potions in your inventory to be searched for!\n";  
            } else {
            string name = getStringInput("Enter potion name: ");
            Potion *found = tree.search(name);
            if (found)
                found->print();
            else
                cout << "Potion not found.\n";
            }
        }
        else if (menuChoice == 4) {
            if (potions.empty()){
                cout << "You have no potions in your inventory to be deleted!\n";  
            } else {
            string name = getStringInput("Enter potion name: ");
            tree.remove(name);
            potions.erase(remove_if(potions.begin(), potions.end(), [&](const Potion &p){ return p.name == name; }),potions.end());
            cout << "This Potion has been sent into the depths of the archive, never to be found again!\n";
            }
        }
        else if (menuChoice == 5) {
            if (potions.empty()){
                cout << "You have no potions in your inventory to be cleared!\n";
            } else {
            tree.clear();
            potions.clear();
            cout << "All potions cleared!\n";
            }
        }
        else if (menuChoice == 6) {
            selectSorting();
            RedBlackTree newTree(sortFunc);
            for (const auto &p : potions)
                newTree.insert(p);
            tree.clear();
            tree = std::move(newTree);
            cout << "Sorting method changed!\n";
        }
        else if (menuChoice == 7) {
            cout << "Thank you for visiting the Potion Creation Station! Good luck with future adventures!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}

