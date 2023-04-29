#include <iostream>
#include <string>
using namespace std;

#ifndef PLANET_H
#define PLANET_H

class Planet {
    public:
        Planet();
        Planet(string userName, string userDescription, int userFuelRequired, int userHostility, string userSize);
        Planet(string userElementN1, string userElementN2, string userElementN3, double userElementM1, double userElementM2, double userElementM3);
        void printInfo();

        string get_name();
        string get_description();
        int get_fuel_required();
        int get_hostility();
        
        void set_name(string);
        void set_description(string);
        void set_fuel_required(int);
        void set_hostility(int);

        string get_size();
        void set_size(string);
        double get_sizeMult();
        void set_sizeMult(double);

        string getElementName1();
        void setElementName1(string);
        double getElementMult1();
        void setElementMult1(double);
        
        string getElementName2();
        void setElementName2(string);
        double getElementMult2();
        void setElementMult2(double);

        string getElementName3();
        void setElementName3(string);
        double getElementMult3();
        void setElementMult3(double);

    private:
        string name;
        string description;
        int fuel_required;
        int hostility;

        string elementName1;
        double elementMult1;

        string elementName2;
        double elementMult2;

        string elementName3;
        double elementMult3;

        string size;
        double size_mult;
};

#endif