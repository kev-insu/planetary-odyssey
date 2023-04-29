#include <iostream>
#include <string>

#include "RandomEvent.h"
#include "ExplorationEvent.h"

ExplorationEvent::ExplorationEvent() {
    success_rate = 80;
    description = "You see an asteroid flying down towards the planet horizon, and it collides with the surface. Would you like to approach the point of impact or ignore?";
    chosen_option = true;
    planet_location = "Mars";
}

ExplorationEvent::ExplorationEvent(int userSuccessRate, string userDescription, string userPlanetLocation) {
    success_rate = userSuccessRate;
    description = userDescription;
    chosen_option = true;
    planet_location = userPlanetLocation;
}
string ExplorationEvent::get_planet_location() {
    return planet_location;
}
void ExplorationEvent::set_planet_location(string userPlanetLocation) {
    planet_location = userPlanetLocation;
}