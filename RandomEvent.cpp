#include <iostream>
#include <string>

#include "RandomEvent.h"
using namespace std;

RandomEvent::RandomEvent() {
    success_rate = 80.00;
    description = "There appears to be an unknown figure standing in the distance. Would you like to approach the figure or ignore?";
    success_description = "Success!";
    failure_description = "Failure.";
    chosen_option = true;
}

RandomEvent::RandomEvent(double userSuccessRate, string userDescription, string userSuccessDescription, string userFailureDescription) {
    success_rate = userSuccessRate;
    description = userDescription;
    success_description = userSuccessDescription;
    failure_description = userFailureDescription;
    chosen_option = true;
}

double RandomEvent::get_success_rate() {
    return success_rate;
}

string RandomEvent::get_description() {
    return description;
}

bool RandomEvent::get_chosen_option() {
    return chosen_option;
}

string RandomEvent::get_success_description() {
    return success_description;
}

string RandomEvent::get_failure_description() {
    return failure_description;
}

void RandomEvent::set_success_rate(double userSuccessRate) {
    success_rate = userSuccessRate;
}

void RandomEvent::set_description(string userDescription) {
    description = userDescription;
}

void RandomEvent::set_success_description(string userSuccessDescription) {
    success_description = userSuccessDescription;
}

void RandomEvent::set_failure_description(string userFailureDescription) {
    failure_description = userFailureDescription;
}

void RandomEvent::set_chosen_option(bool userOption) {
    chosen_option = userOption;
}