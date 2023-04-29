#ifndef EXPLORATIONEVENT_H
#define EXPLORATIONEVENT_H
using namespace std;
#include <string>
#include "RandomEvent.h"

class ExplorationEvent : public RandomEvent {
    private:
        string planet_location;
        double event_multiplier;
    public:
        ExplorationEvent();
        ExplorationEvent(double, string, string, string, string, double);
        string get_planet_location();
        void set_planet_location(string);
        double get_event_multiplier();
        void set_event_multiplier(double);
};

#endif