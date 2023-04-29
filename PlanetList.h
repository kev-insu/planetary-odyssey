#include <iostream>
#include <string>

#include "Planet.h"
using namespace std;

#ifndef PLANETLIST_H
#define PLANETLIST_H

class PlanetList {
    public:
        PlanetList();
        PlanetList(int num);
        ~PlanetList();

        bool planetAdd(Planet newPlanet);
        bool planetRemove(int index);
        void printPlanetList();
        void deletePlanetList();

        int getNumPlanets();
        int getMaxPlanets();
        void printPlanetName(int);
        void printPlanetInfo(int);

        Planet getPlanet(int);

        string getPlanetName(int);
        string getDescription(int);
        int getFuelRequired(int);
        int getHostility(int);
        string getSize(int);

    private:
        Planet* planetList = nullptr;
        int max_planets = 0;
        int num_planets = 0;
};

#endif