#include <iostream>
#include <string>

#include "PlanetList.h"
#include "Planet.h"

using namespace std;

PlanetList::PlanetList() {
    planetList = nullptr;
    max_planets = 0;
    num_planets = 0;
}
PlanetList::PlanetList(int num) {
    if (num <= 0) {
        max_planets = 0;
        planetList = nullptr;
    }
    else {
        max_planets = num;
        planetList = new Planet[max_planets];
    }

    num_planets = 0;
}

bool PlanetList::planetAdd(Planet planet) {
    if (num_planets >= max_planets) {
        return false;
    }
    else {
        planetList[num_planets] = planet;
        num_planets++;
        return true;
    }
}
bool PlanetList::planetRemove(int index) {
    for (int i = index; i < num_planets - 1; i++) {
        planetList[i] = planetList[i + 1];
    }
    num_planets -= 1;
    return true;
}

void PlanetList::printPlanetList() {
    int index;
    for (int index = 0; index < num_planets; index++) {
        cout << "Name: " << planetList[index].get_name() << endl;
        cout << "Description: " << planetList[index].get_description() << endl;
        cout << "Fuel required: " << planetList[index].get_fuel_required() << endl;
        cout << "Hostility: " << planetList[index].get_hostility() << endl;
        cout << "Size: " << planetList[index].get_size() << endl << endl;
    }
}

void PlanetList::deletePlanetList() {
    if (planetList != nullptr) {
        delete[] planetList;
        planetList = nullptr;
        num_planets = 0;
        max_planets = 0;
    }
}

PlanetList::~PlanetList() {
    if (planetList == nullptr) {
        cout << "|| Memory is released.                                      ||" << endl;
    }
    else {
        cout << "|| Memory was not able to be released.                   ||" << endl;
        delete[] planetList;
        planetList = nullptr;
        max_planets = 0;
        num_planets = 0;
    }
}

int PlanetList::getNumPlanets() {
    return num_planets;
}

int PlanetList::getMaxPlanets() {
    return max_planets;
}

void PlanetList::printPlanetName(int index) {
    cout << planetList[index].get_name();


}

void PlanetList::printPlanetInfo(int index) {
    cout << "Name: " << planetList[index].get_name() << endl;
    cout << "Description: " << planetList[index].get_description() << endl;
    cout << "Fuel recommended: " << planetList[index].get_fuel_required() << endl;
    cout << "Hostility: " << planetList[index].get_hostility() << endl;
    cout << "Size: " << planetList[index].get_size() << endl << endl;
}

Planet PlanetList::getPlanet(int index) {
    return planetList[index];
}

string PlanetList::getPlanetName(int index) {
    return planetList[index].get_name();
}

string PlanetList::getDescription(int index) {
    return planetList[index].get_description();
}

int PlanetList::getFuelRequired(int index) {
    return planetList[index].get_fuel_required();
}

int PlanetList::getHostility(int index) {
    return planetList[index].get_hostility();
}

string PlanetList::getSize(int index) {
    return planetList[index].get_size();
}