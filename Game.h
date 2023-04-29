#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "Spaceship.h"
using namespace std;

class Game {
    private:
        int cash;
        int num_odysseys;
        Spaceship shipObject;
        bool firstRun;
    public:
        Game();
        Game(int, int, Spaceship, bool);
        void printStats();

        int getCash();
        int getNumOdysseys();
        Spaceship getSpaceship();
        bool getFirstRun();

        void setCash(int);
        void setNumOdysseys(int);
        void setSpaceship(Spaceship);
        void setFirstRun(bool);
};

#endif

/* To-Do:
multipliers:
1. numOdysseysExplored y = ln(x) done
2. hosility multiplier (1 to 2x) done
3. ship multiplier? (1.1x) * n done
4. current_crew (1.5x) * n done
5. planet size multiplier (from 1.1x to 2) done
6. element multiplier


add progress bar and cur/cap for buying and selling fuel/crew done

add event occurrences during gameplay
polish program from bugs
add more custom spaceships

*/