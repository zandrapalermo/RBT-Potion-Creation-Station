#ifndef POTION_H
#define POTION_H

#include <string>
#include <iostream>

using namespace std;

struct Potion {
    string name;
    int strength;
    int speed;
    int health;

    Potion(string n = "", int str = 0, int spd = 0, int hp = 0)
        : name(n), strength(str), speed(spd), health(hp) {}

    int totalStats() const {
        return strength + speed + health;
    }

    void print() const {
        cout << name << " (STR: " << strength
                  << ", SPD: " << speed
                  << ", HP: " << health
                  << ", Total: " << totalStats()
                  << ")\n";
    }
};

#endif
