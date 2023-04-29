#include <iostream>
#include <string>

#include "Planet.h"

Planet::Planet() {
    name = "Mars";
    description = "A small, orange, and terrestrial planet composed of iron, nickel, and sulfur.";
    fuel_required = 50;
    hostility = 1;
    size = "small";
    size_mult = 1.2;

    elementName1 = "iron";
    elementName2 = "nickel";
    elementName3 = "sulfur";
    elementMult1 = 1.26;
    elementMult2 = 1.28;
    elementMult3 = 1.16;
}

Planet::Planet(string userName, string userDescription, int userFuelRequired, int userHostility, string userSize) {
    name = userName;
    description = userDescription;
    fuel_required = userFuelRequired;
    hostility = userHostility;
    size = userSize;
    size_mult = 1.3;
    elementName1 = "hydrogen";
    elementName2 = "helium";
    elementName3 = "carbon";
    elementMult1 = 1.00;
    elementMult2 = 1.01;
    elementMult3 = 1.06;
}

Planet::Planet(string userElementN1, string userElementN2, string userElementN3, double userElementM1, double userElementM2, double userElementM3) {
    elementName1 = userElementN1;
    elementName2 = userElementN2;
    elementName3 = userElementN3;
    elementMult1 = userElementM1;
    elementMult2 = userElementM2;
    elementMult3 = userElementM3;
}

void Planet::printInfo() {
    cout << "Planet name: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Fuel recommended: " << fuel_required << endl;
    cout << "Hostility: " << hostility << endl;
    cout << "Size: " << size << endl;
}

string Planet::get_name() {
    return name;
}

string Planet::get_description() {
    return description;
}

int Planet::get_fuel_required() {
    return fuel_required;
}

int Planet::get_hostility() {
    return hostility;
}

void Planet::set_name(string userName) {
    name = userName;
}

void Planet::set_description(string userDescription) {
    description = userDescription;
}

void Planet::set_fuel_required(int userFuelRequired) {
    fuel_required = userFuelRequired;
}

void Planet::set_hostility(int userHostility) {
    hostility = userHostility;
}

string Planet::get_size() {
    return size;
}

void Planet::set_size(string userSize) {
    size = userSize;
}

double Planet::get_sizeMult() {
    return size_mult;
}
void Planet::set_sizeMult(double userSizeMult) {
    size_mult = userSizeMult;
}

string Planet::getElementName1() {
    return elementName1;
}

void Planet::setElementName1(string userElementName1) {
    elementName1 = userElementName1;

}

double Planet::getElementMult1() {
    return elementMult1;
}

void Planet::setElementMult1(double userElementMult1) {
    elementMult1 = userElementMult1;
}


string Planet::getElementName2() {
    return elementName2;
}

void Planet::setElementName2(string userElementName2) {
    elementName2 = userElementName2;

}

double Planet::getElementMult2() {
    return elementMult2;
}

void Planet::setElementMult2(double userElementMult2) {
    elementMult2 = userElementMult2;
}


string Planet::getElementName3() {
    return elementName3;
}

void Planet::setElementName3(string userElementName3) {
    elementName3 = userElementName3;

}

double Planet::getElementMult3() {
    return elementMult3;
}

void Planet::setElementMult3(double userElementMult3) {
    elementMult3 = userElementMult3;
}