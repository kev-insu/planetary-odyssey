#include <iostream>
#include <string>

#include "RandomEvent.h"

RandomEvent::RandomEvent() {
    success_rate = 80;
    description = "There appears to be an unknown figure standing in the distance. Would you like to approach the figure or ignore?";
    chosen_option = true;
}

RandomEvent::RandomEvent(int userSuccessRate, string userDescription) {
    success_rate = userSuccessRate;
    description = userDescription;
    chosen_option = true;
}

int RandomEvent::get_success_rate() {
    return success_rate;
}

string RandomEvent::get_description() {
    return description;
}

bool RandomEvent::get_chosen_option() {
    return chosen_option;
}

void RandomEvent::set_success_rate(int userSuccessRate) {
    success_rate = userSuccessRate;
}

void RandomEvent::set_description(string userDescription) {
    description = userDescription;
}

void RandomEvent::set_chosen_option(bool userOption) {
    chosen_option = userOption;
}