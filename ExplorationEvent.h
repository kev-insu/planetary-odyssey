#ifndef EXPLORATIONEVENT_H
#define EXPLORATIONEVENT_H
using namespace std;
#include "RandomEvent.h"

class ExplorationEvent : public RandomEvent {
    private:
        string planet_location;
    public:
        ExplorationEvent();
        ExplorationEvent(int, string, string);
        string get_planet_location();
        void set_planet_location(string);
};

#endif