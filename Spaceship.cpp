#include <iostream>
using namespace std;

#include "Spaceship.h"

Spaceship::Spaceship() {
    capacity_fuel = 100;
    capacity_crew = 10;
    current_fuel = 100;
    current_crew = 10;
    ship_name = "Copper";
    ship_cost = 100;
    ship_value = ship_cost / 2;
}

Spaceship::Spaceship(string userShipName, int userShipCost, int userFuel, int userCrew) {
    capacity_fuel = userFuel;
    capacity_crew = userCrew;
    current_fuel = capacity_fuel;
    current_crew = capacity_crew;
    ship_name = userShipName;
    ship_cost = userShipCost;
    ship_value = userShipCost / 2;
}

void Spaceship::printInfo() {
    cout << "Spaceship Info:" << endl;
    if (ship_name != "None") {
        cout << "   Ship: " << ship_name << " Spaceship" << endl
             << "   Ship value: " << ship_value << " cash" << endl
             << "   Fuel: " << current_fuel << "/" << capacity_fuel << " units" << endl
             << "   Crewmates: " << current_crew << "/" << capacity_crew << " occupied" << endl;
    }
    else {
        cout << "   Ship: " << ship_name << endl;
    }
}

void Spaceship::ship_addFuel(int userFuel) {
    current_fuel += userFuel;
    if (current_fuel > capacity_fuel) {
        current_fuel = capacity_fuel;
    }
}

void Spaceship::ship_onBoard() {
    current_crew = capacity_crew;
}

void Spaceship::ship_offBoard() {
    current_crew = 0;
}

int Spaceship::get_capacity_fuel() {
    return capacity_fuel;
}

int Spaceship::get_capacity_crew() {
    return capacity_crew;
}

int Spaceship::get_current_fuel() {
    return current_fuel;
}

int Spaceship::get_current_crew() {
    return current_crew;
}

string Spaceship::get_ship_name() {
    return ship_name;
}

int Spaceship::get_ship_cost() {
    return ship_cost;
}

int Spaceship::get_ship_value() {
    return ship_value;
}

void Spaceship::set_capacity_fuel(int userFuelCapacity) {
    capacity_fuel = userFuelCapacity;
}

void Spaceship::set_capacity_crew(int userCrewCapacity) {
    capacity_crew = userCrewCapacity;
}

void Spaceship::set_current_fuel(int userCurrentFuel) {
    current_fuel = userCurrentFuel;
}

void Spaceship::set_current_crew(int userCurrentCrew) {
    current_crew = userCurrentCrew;
}

void Spaceship::set_ship_name(string userShipName) {
    ship_name = userShipName;
}

void Spaceship::set_ship_cost(int userShipCost) {
    ship_cost = userShipCost;
}

void Spaceship::set_ship_value(int userShipValue) {
    ship_value = userShipValue;
}