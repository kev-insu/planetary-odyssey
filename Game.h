#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "Spaceship.h"
using namespace std;

class Game {
    private:
        double cash;
        int num_odysseys;
        Spaceship shipObject;
        bool firstRun;
    public:
        Game();
        Game(double, int, Spaceship, bool);
        void printStats();

        double getCash();
        int getNumOdysseys();
        Spaceship getSpaceship();
        bool getFirstRun();

        void setCash(double);
        void setNumOdysseys(int);
        void setSpaceship(Spaceship);
        void setFirstRun(bool);
};

#endif