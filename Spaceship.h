#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <iostream>
#include <string>
using namespace std;

class Spaceship {
    protected:
        double capacity_fuel; // stores the value of the maximum amount of fuel the spaceship may hold
        int capacity_crew; // stores the value of the maximum amount of fuel the spaceship may hold
        double current_fuel; // stores the value of the amount of fuel the spaceship has at the current time
        int current_crew; // stores the value of the amount of crewmates the ship has at the current time
        string ship_name;
        double ship_cost;
        int ship_value; // stores the spaceship’s monetary value
        int ship_index;
    public:
        Spaceship();
        Spaceship(string userShipName, double userShipCost, double userFuel, int userCrew, int ship_index);
        void printInfos();
        void ship_addFuel(double);
        void ship_onBoard();
        void ship_offBoard();

        double get_capacity_fuel();
        int get_capacity_crew();
        double get_current_fuel();
        int get_current_crew();
        string get_ship_name();
        double get_ship_cost();
        int get_ship_value();
        int get_ship_index();

        void set_capacity_fuel(double);
        void set_capacity_crew(int);
        void set_current_fuel(double);
        void set_current_crew(int);
        void set_ship_name(string);
        void set_ship_cost(double);
        void set_ship_value(int);
        void set_ship_index(int);
};

#endif