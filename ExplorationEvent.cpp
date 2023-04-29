#include <iostream>
#include <string>

#include "RandomEvent.h"
#include "ExplorationEvent.h"

ExplorationEvent::ExplorationEvent() : RandomEvent() {
    /* success_rate = 80.0;
    description = "You see the faint shadow of a martian looming in the distance.";
    chosen_option = true; */
    planet_location = "Mars";
    event_multiplier = 1.1;
}

ExplorationEvent::ExplorationEvent(double userSuccessRate, string userDescription, string userSuccessDescription, string userFailureDescription,
    string userPlanetLocation, double userEventMultiplier) : RandomEvent(userSuccessRate, userDescription, userSuccessDescription, userFailureDescription) {
        
    planet_location = userPlanetLocation;
    event_multiplier = userEventMultiplier;
}
string ExplorationEvent::get_planet_location() {
    return planet_location;
}
void ExplorationEvent::set_planet_location(string userPlanetLocation) {
    planet_location = userPlanetLocation;
}

double ExplorationEvent::get_event_multiplier() {
    return event_multiplier;
}

void ExplorationEvent::set_event_multiplier(double userEventMultiplier) {
    event_multiplier = userEventMultiplier;
}