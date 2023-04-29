#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <iostream>
#include <string>
using namespace std;

class Spaceship {
    protected:
        int capacity_fuel; // stores the value of the maximum amount of fuel the spaceship may hold
        int capacity_crew; // stores the value of the maximum amount of fuel the spaceship may hold
        int current_fuel; // stores the value of the amount of fuel the spaceship has at the current time
        int current_crew; // stores the value of the amount of crewmates the ship has at the current time
        string ship_name;
        int ship_cost;
        int ship_value; // stores the spaceship’s monetary value
    public:
        Spaceship();
        Spaceship(string userShipName, int userShipCost, int userFuel, int userCrew);
        void printInfo();
        void ship_addFuel(int);
        void ship_onBoard();
        void ship_offBoard();
        int get_capacity_fuel();
        int get_capacity_crew();
        int get_current_fuel();
        int get_current_crew();
        string get_ship_name();
        int get_ship_cost();
        int get_ship_value();
        void set_capacity_fuel(int);
        void set_capacity_crew(int);
        void set_current_fuel(int);
        void set_current_crew(int);
        void set_ship_name(string);
        void set_ship_cost(int);
        void set_ship_value(int);
};

#endif