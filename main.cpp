#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cmath>

#include "Spaceship.h"
#include "Game.h"
#include "Planet.h"
#include "PlanetList.h"
#include "RandomEvent.h"
#include "ExplorationEvent.h"

using namespace std;

void outputBuffer() {
    string buffer;
    cout << "|| Press any key to return.                                 ||" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cin >> buffer;
}

void outputContBuffer() {
    string buffer;
    cout << "|| Press any key to continue.                               ||" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cin >> buffer;
}

void progressBuffer() {
    string buffer;
    cout << "|| Press any key to roll and progress.                      ||" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cin >> buffer;
}

template <typename T>
void progressBar(T cur, T max) { // creates a progress bar with 2 percent increments per character
    T percentNum = (cur * 100) / max;
    int percent;
    
    cout << "   [";

    if (percentNum > 100) {
        percent = 100;
    }
    else {
        percent = percentNum;
    }

    for (int i = 0; i < (percent / 2); i++) {
        cout << "#";
    }
    for (int j = 0; j < (50 - (percent / 2)); j++) {
        cout << " ";
    }
    if (percentNum > 100) {
        cout << "] " << "100%" << endl;
    }
    else {
        cout << "] " << ((cur * 100) / max) << "%" << endl;
    }
}

void load(string filename, Game& player, bool& loaded) { // loads save data from a specified file
    ifstream inStream(filename);
    if (!inStream.is_open()) {
        loaded = false;
    }
    else {
        int temp_int;
        double temp_double;
        string temp_string;
        bool temp_bool;
        Spaceship tempShip;

        inStream >> temp_double;
        player.setCash(temp_double);
        inStream >> temp_int;
        player.setNumOdysseys(temp_int);
        inStream.ignore();
        getline(inStream, temp_string);
        tempShip.set_ship_name(temp_string);
        inStream >> temp_int;  
        tempShip.set_ship_value(temp_int);   
        inStream >> temp_double;
        tempShip.set_capacity_fuel(temp_double);
        inStream >> temp_int;
        tempShip.set_capacity_crew(temp_int);
        inStream >> temp_double;
        tempShip.set_current_fuel(temp_double);
        inStream >> temp_int;
        tempShip.set_current_crew(temp_int);
        inStream >> temp_int;
        tempShip.set_ship_index(temp_int);

        player.setSpaceship(tempShip);

        inStream >> temp_bool;
        player.setFirstRun(temp_bool);
    }
    
    if (!inStream.is_open() && player.getFirstRun() == false) {
        cout << "--------------------------------------------------------------" << endl;
        cout << "File not found!" << endl;
    }

    inStream.close();
}

void save(string filename, Game& player) { // saves current in-game data to a specified file
    ofstream outStream(filename);

    outStream << fixed << setprecision(2);
    outStream << player.getCash() << endl;
    outStream << player.getNumOdysseys() << endl;

    Spaceship tempShip = player.getSpaceship();

    outStream << tempShip.get_ship_name() << endl;
    outStream << tempShip.get_ship_value() << endl;
    outStream << tempShip.get_capacity_fuel() << endl;
    outStream << tempShip.get_capacity_crew() << endl;
    outStream << tempShip.get_current_fuel() << endl;
    outStream << tempShip.get_current_crew() << endl;
    outStream << tempShip.get_ship_index() << endl;

    outStream << player.getFirstRun() << endl;
    outStream << scientific;
    outStream.close();
}

double logBase(double base, double num) {
    return log(num) / log(base);
}

bool Proc(int hit, int total) {
    if ((rand() % total) < hit) {
        return true;
    }
    else {
        return false;
    }
}

void spaceshipData(Spaceship ships[]) { // contains all data from purchasable spaceships
    ships[1] = Spaceship("Iron", 1000, 200, 22, 2);
    ships[2] = Spaceship("Bronze", 4000, 400, 33, 3);
    ships[3] = Spaceship("Silver", 16000, 800, 50, 4);
    ships[4] = Spaceship("Gold", 64000, 1600, 75, 5);
    ships[5] = Spaceship("Platinum", 256000, 3200, 113, 6);
    ships[6] = Spaceship("Diamond", 1024000, 6400, 170, 7);
    ships[7] = Spaceship("Galactic Incarnate 1", 4096000, 12800, 250, 8);
}

Spaceship calculateGalacticIncarnateShip(int tier) { // calculates the values for Galactic Incarnate Ship 2+
    Spaceship tempShip;
    int index = tier + 7;
    string name = "Galactic Incarnate " + to_string(tier);
    double cost = 1000 * pow(4, tier + 5);
    double fuel = 200 * pow(2, tier + 5);
    int crew = 15 * pow(1.5, tier + 5);

    tempShip = Spaceship(name, cost, fuel, crew, index);
    return tempShip;
}

double sellShip(Spaceship ship) { // calculates ship value from selling
    double cashReturned = 0;
    cout << "Spaceship value: + " << ship.get_ship_value() << " cash" << endl;
    cashReturned += ship.get_ship_value();

    double fuelToCash = (ship.get_current_fuel() / 2);
    cout << "Fuel:            + " << fuelToCash << " cash" << endl;
    cashReturned += fuelToCash;

    cout << "Crewmates:       + " << ship.get_current_crew() * 5 << " cash" << endl;
    cashReturned += ship.get_current_crew() * 5;

    return cashReturned;
}

bool hasFuel(Game player) {
    if (player.getSpaceship().get_current_fuel() == 0) {
        cout << "--------------------------------------------------------------" << endl;
        cout << "Please fuel up your spaceship before performing this action." << endl;
        cout << endl;
        outputBuffer();
        return false;
    }
    return true;
}

bool hasCrew(Game player) {
    if (player.getSpaceship().get_current_crew() == 0) {
        cout << "--------------------------------------------------------------" << endl;
        cout << "Please add crewmates to your spaceship before performing this action." << endl;
        cout << endl;
        outputBuffer();
        return false;
    }
    return true;
}

bool hasEnoughCash(Game player, double cost) {
    if (player.getCash() < cost) {
        cout << "--------------------------------------------------------------" << endl;
        cout << "You do not have enough cash." << endl;
        cout << endl;
        outputBuffer();
        return false;
    }

    return true;
}

Spaceship calcuFuel(Spaceship ship, double num) { // adds or subtracts fuel
    double cur = ship.get_current_fuel();
    double calc = cur + num;

    Spaceship tempShip = ship;
    tempShip.set_current_fuel(cur + num);

    if (cur + num < 0) {
        tempShip.set_current_fuel(0);
    }

    return tempShip;
}

Spaceship calcuCrew(Spaceship ship, int num) { // adds or subtracts crewmates
    int cur = ship.get_current_crew();
    int calc = cur + num;

    Spaceship tempShip = ship;
    tempShip.set_current_crew(cur + num);

    if (cur + num < 0) {
        tempShip.set_current_crew(0);
    }

    return tempShip;
}

double calcuCash(Game player, double num) { // adds or subtracts cash
    double cur = player.getCash();
    double calc = cur + num;

    player.setCash(cur + num);

    return player.getCash();
}

Spaceship calculateFuel(Spaceship ship, double num, bool& calcFuel) { // adds or subtracts fuel
    double cur = ship.get_current_fuel();
    double calc = cur + num;
    cout << "Fuel: " << cur;
    if (num >= 0) {
        cout << " + ";
    }
    else {
        cout << " - ";
    }
    cout << abs(num) << endl;

    Spaceship tempShip = ship;
    tempShip.set_current_fuel(cur + num);

    if (cur + num < 0) {
        tempShip.set_current_fuel(0);
    }

    calcFuel = true;

    return tempShip;
}

Spaceship calculateCrew(Spaceship ship, int num, bool& calcCrew) { // adds or subtracts crewmates
    int cur = ship.get_current_crew();
    int calc = cur + num;
    cout << "Crewmates: " << cur;
    if (num >= 0) {
        cout << " + ";
    }
    else {
        cout << " - ";
    }
    cout << abs(num) << endl;

    Spaceship tempShip = ship;
    tempShip.set_current_crew(cur + num);

    if (cur + num < 0) {
        tempShip.set_current_crew(0);
    }
    calcCrew = true;

    return tempShip;
}

double calculateCash(Game player, double num, bool& calcCash) { // adds or subtracts cash
    double cur = player.getCash();
    double calc = cur + num;
    cout << "Cash: " << cur;
    if (num >= 0) {
        cout << " + ";
    }
    else {
        cout << " - ";
    }
    cout << abs(num) << endl;

    player.setCash(cur + num);
    calcCash = true;

    return player.getCash();
}

void printCalculations(Spaceship ship, bool& calcFuel, bool& calcCrew, bool &calcCash, double cash) { // displays counts after calculations
    if (calcFuel) {
        cout << "You now have " << ship.get_current_fuel() << "/" << ship.get_capacity_fuel() << " units of fuel." << endl;
        calcFuel = false;
    }

    if (calcCrew) {
        cout << "You now have " << ship.get_current_crew() << "/" << ship.get_capacity_crew() << " occupied." << endl;
        calcCrew = false;
    }

    if (calcCash) {
        cout << "You now have " << cash << " cash." << endl;
        calcCash = false;
    }
}

Planet createRandomPlanet(Game player) { // creates a random planet; over 960 million combinations of unique planets by properties, (when paired with unique names, over 10 quadrillion combinations)
    // random planet name
    string name;
    int temp = rand();
    for (int i = 0; i < 3; i++) {
        name += (65 + rand() % 26);
    }

    name += '-';
    for (int j = 0; j < 3; j++) {
        name += (48 + rand() % 10);
    }

    // random planet description - Ex: A (size), (color), and (type) planet composed of (element 1), (element 2), and (element 3).
    int numSize = 11;
    int numColor = 12;
    int numType = 5;
    int numElement = 118;
    string planetSize[numSize] = {"dwarf", "miniscule", "small", "medium-sized", "large", "huge", "giant", "massive", "vast", "colossal", "galactic"};
    string planetSizeVar[numSize] = {"Dwarf", "Miniscule", "Small", "Medium-sized", "Large", "Huge", "Giant", "Massive", "Vast", "Colossal", "Galactic"};
    string planetColor[numColor] = {"pink", "red", "yellow", "green", "blue", "purple", "white", "black", "lavender", "beige", "jade", "silver"};
    string planetType[numType] = {"gaseous", "terrestrial", "aquatic", "clear", "cloudy"};
    string planetElements[numElement] = {"hydrogen", "helium", "lithium", "beryllium", "boron", "carbon", "nitrogen", "oxygen", "flourine", "neon", "sodium", "magnesium", "alnuminum", 
    "silicon", "phosphorus", "sulfur", "chlorine", "argon", "potassium", "calcium", "scandium", "titanium", "vanadium", "chromium", "manganese", "iron", "cobalt", "nickel", "copper",
    "zinc", "gallium", "germanium", "arsenic", "selenium", "bromine", "krypton", "rubidium", "stronium", "yttrium", "zirconium", "niobium", "molybdenum", "technetium", "ruthenium",
    "rhodium", "palladium", "silver", "cadmium", "indium", "tin", "antimony", "tellurium", "iodine", "xenon", "caesium", "barium", "lanthanum", "cerium", "praseodymium", "neodymium",
    "promethium", "samarium", "europium", "gadolinium", "terbium", "dysprosium", "holmium", "erbium", "thulium", "ytterbium", "lutetium", "hafnium", "tantalum", "tungsten",
    "rhenium", "osmium", "iridium", "platinum", "gold", "mercury", "thallium", "lead", "bismuth", "polonium", "astatine", "radon", "fracnium", "radium", "actinium", "thorium",
    "protactinium", "uranium", "neptunium", "plutonium", "americium", "curium", "berkelium", "californium", "einsteinium", "fermium", "mendelevium", "nobelium", "lawrencium",
    "rutherfordium", "dubnium", "seaborgium", "bhorium", "hassium", "meitnerium", "darmstadtium", "roentgenium", "copernicium", "nihonium", "flerovium", "moscovium", "livermorium",
    "tennessine", "oganesson"};

    // selects elements
    int tempIndex;
    int indexFirstElement = (rand() % numElement);

    tempIndex = rand() % numElement;
    while (tempIndex == indexFirstElement) {
        tempIndex = rand() % numElement;
    }
    int indexSecondElement = tempIndex;

    tempIndex = rand() % numElement;
    while (tempIndex == indexFirstElement || tempIndex == indexSecondElement) {
        tempIndex = rand() % numElement;
    }
    int indexThirdElement = tempIndex;

    string firstElement = planetElements[indexFirstElement];
    string secondElement = planetElements[indexSecondElement];
    string thirdElement = planetElements[indexThirdElement];

    // sets size
    int sizeIndex = rand() % numSize;
    string selectedSize = planetSize[sizeIndex];
    string varSize = planetSizeVar[sizeIndex];

    string selectedColor = planetColor[rand() % numColor];
    string selectedType = planetType[rand() % numType];

    // creates string of description
    string description = "A " + selectedSize + ", " + selectedColor + ", and " + selectedType + " planet composed of " + firstElement + ", " + secondElement + ", and " + thirdElement + ".";

    // random hostility
    int hostility;
    if (player.getSpaceship().get_ship_index() > 6) {
        hostility = player.getSpaceship().get_ship_index() - 3 + (rand() % 7);
    }
    else {
        hostility = 1 + (rand() % 10);
    }


    // random fuel_required
    int fuel_required;
    if (hostility == 1) {
        fuel_required = 50;
    }
    else {
        fuel_required = 100 * pow(2, hostility - 2);
    }

    double index1 = indexFirstElement;
    double index2 = indexSecondElement;
    double index3 = indexThirdElement;

    Planet tempPlanet = Planet(firstElement, secondElement, thirdElement, 1.01 + (index1 / 100), 1.01 + (index2 / 100), 1.01 + (index3 / 100));
    tempPlanet.set_name(name);
    tempPlanet.set_description(description);
    tempPlanet.set_fuel_required(fuel_required);
    tempPlanet.set_hostility(hostility);
    tempPlanet.set_size(selectedSize);
    tempPlanet.set_sizeMult(((double)sizeIndex / 10) + 1);
    
    return tempPlanet;
}

bool hasSpaceship(Game player) {
    if (player.getSpaceship().get_ship_name() == "None") {
        cout << "--------------------------------------------------------------" << endl;
        cout << "Please buy a spaceship before performing this action." << endl;
        cout << endl;
        outputBuffer();
        return false;
    }
    return true;
}

void printFuelCrewProgressBar(Game player) {
    cout << "Fuel: " << player.getSpaceship().get_current_fuel() << "/" << player.getSpaceship().get_capacity_fuel() << endl;
    cout << "Crew: " << player.getSpaceship().get_current_crew() << "/" << player.getSpaceship().get_capacity_crew() << endl;
    progressBar(player.getSpaceship().get_current_fuel(), player.getSpaceship().get_capacity_fuel());
    progressBar(player.getSpaceship().get_current_crew(), player.getSpaceship().get_capacity_crew());
}

void printAllStats(Game player) {
    cout << "--------------------------------------------------------------" << endl;
    player.printStats();
    if (player.getSpaceship().get_ship_name() != "None") {
        cout << endl << "Fuel / Crewmates:" << endl;
        progressBar(player.getSpaceship().get_current_fuel(), player.getSpaceship().get_capacity_fuel());
        progressBar(player.getSpaceship().get_current_crew(), player.getSpaceship().get_capacity_crew());
    }

    cout << endl;
}

void uEventData(ExplorationEvent &mEvent, ExplorationEvent &sEvent) {
    mEvent = ExplorationEvent(80.00, "You see the faint shadow of a martian looming in the distance.",
    "The friendly martian greets you and offers you fuel and cash!", "The martian angrily lashes towards the spaceship and damages it.", "Mars", 1.1);
    sEvent = ExplorationEvent(50.00, "A giant surfaces from the gaseous liquids of the planet.",
    "The giant, gentle in its maneuver, grants you a gift.", "The giant grazes your spaceship with its inconcievably large hand.", "Saturn", 1.25);
}

RandomEvent createRandomEvent(Game player, Planet planet) {
    RandomEvent tempEvent;
    // create success rate;
    double success = 40.0 + 60.0 * ((rand() % player.getSpaceship().get_ship_index()) / 500.0);
    success *= .9 + ((double)(rand() % 21) / 100.0);
    if (success > 100) {
        success = 100.00;
    }

    int sizeRockType = 5;
    string rockType[sizeRockType] = {"pebble", "boulder", "comet", "asteroid", "star"};
    int randRockType = rand() % sizeRockType;
    string impact = rockType[randRockType];
    string description = "A(n) " + planet.get_size() + " " + impact + " crashes into " + planet.get_name() + ".";
    string success_description = "You successfully extracted the " + planet.get_size() + " " + impact + "'s treasures!";
    string failure_description = "The " + impact + " explodes and hurts your mining crewmates as well as the ship.";

    tempEvent = RandomEvent(success, description, success_description, failure_description);

    return tempEvent;
}

void EventCalc(Game &player, Planet planet, double &pCur, double &pMax, ExplorationEvent mEvent, ExplorationEvent sEvent) {
    bool hasUniqueEvent = false;
    double successChance;
    string description;
    string success_d;
    string failure_d;
    double uPlanetMult = 1.0;
    string uOption;

    if (planet.get_name() == "Mars" || planet.get_name() == "Saturn") {
        hasUniqueEvent = true;
    }

    if (Proc(60, 100)) {
        hasUniqueEvent = false;
    }

    restart:
    cout << "--------------------------------------------------------------" << endl;
    cout << "| Current planet: " << planet.get_name() << endl;
    cout << "| Hostility: " << planet.get_hostility() << endl << endl;

    if (hasUniqueEvent == false) { // for discovered planets without exploration events
        RandomEvent event = createRandomEvent(player, planet);
        cout << event.get_description() << endl;
        cout << "Success rate: " << event.get_success_rate() << "%" << endl << endl;
        successChance = event.get_success_rate();
        description = event.get_description();
        success_d = event.get_success_description();
        failure_d = event.get_failure_description();

    }
    else if (planet.get_name() == sEvent.get_planet_location()) {
        cout << sEvent.get_description() << endl;
        successChance = sEvent.get_success_rate() + (100 - sEvent.get_success_rate()) * ((rand() % player.getSpaceship().get_ship_index()) / 500.0);
        successChance *= .9 + ((double)(rand() % 21) / 100.0);
        if (successChance > 100) {
            successChance = 100.00;
        }
        cout << "Success rate: " << successChance << "%" << endl << endl;
        description = sEvent.get_description();
        uPlanetMult = sEvent.get_event_multiplier();
        success_d = sEvent.get_success_description();
        failure_d = sEvent.get_failure_description();
    }
    else if (planet.get_name() == mEvent.get_planet_location()) {
        cout << mEvent.get_description() << endl;
        successChance = mEvent.get_success_rate() + (100 - mEvent.get_success_rate()) * ((rand() % player.getSpaceship().get_ship_index()) / 500.0);
        successChance *= .9 + ((double)(rand() % 21) / 100.0);
        if (successChance > 100) {
            successChance = 100.00;
        }
        cout << "Success rate: " << successChance << "%" << endl << endl;
        description = mEvent.get_description();
        uPlanetMult = mEvent.get_event_multiplier();
        success_d = mEvent.get_success_description();
        failure_d = mEvent.get_failure_description();
    }
    cout << endl;
    cout << "Fuel / Crew / Progress Bar:" << endl;
    progressBar(player.getSpaceship().get_current_fuel(), player.getSpaceship().get_capacity_fuel());
    progressBar(player.getSpaceship().get_current_crew(), player.getSpaceship().get_capacity_crew());
    progressBar(pCur, pMax);

    cout << "|| (1) - Approach.                                           ||" << endl;
    cout << "|| (2) - Ignore and keep rolling.                            ||" << endl;
    cout << "--------------------------------------------------------------" << endl;

    cin >> uOption;

    if (uOption != "1" && uOption != "2") {
        string buffer;
        cout << "--------------------------------------------------------------" << endl;
        cout << "|| Please select a valid option.                            ||" << endl;
        cout << "--------------------------------------------------------------" << endl;
        cin >> buffer;
        goto restart;
    }
    if (uOption == "2") {
        return;
    }
    int intSuccess = successChance * 100;
    bool calcSuccess = Proc(intSuccess, 10000);

    cout << "--------------------------------------------------------------" << endl;
    cout << "| Current planet: " << planet.get_name() << endl;
    cout << "| Hostility: " << planet.get_hostility() << endl << endl;

    if (calcSuccess) {
        double curFuel = player.getSpaceship().get_current_fuel();
        double fuelGain = player.getSpaceship().get_capacity_fuel() * (double)pow(.95, player.getSpaceship().get_ship_index()) * ((double(80) + rand() % 41) / 100.0) * 0.025;
        if (fuelGain + curFuel > player.getSpaceship().get_capacity_fuel()) {
            fuelGain = player.getSpaceship().get_capacity_fuel() - curFuel;
        }
        player.setSpaceship(calcuFuel(player.getSpaceship(), fuelGain * uPlanetMult));

        double cashGain = 1000.0 * (double)pow(4, player.getSpaceship().get_ship_index() - 2) * ((double(80) + rand() % 41) / 100.0) * .04;
        player.setCash(calcuCash(player, cashGain));

        cout << success_d << endl;
        cout << "+ " << fuelGain << " fuel." << endl;
        cout << "+ " << cashGain << " cash." << endl;        


    }
    else {
        double curFuel = player.getSpaceship().get_current_fuel();
        int curCrew = player.getSpaceship().get_current_crew();
        double fuelLoss = -player.getSpaceship().get_capacity_fuel() * (double)pow(.95, player.getSpaceship().get_ship_index()) * ((double(80) + rand() % 41) / 100.0) * 0.05;
        int crewLoss = floor((double)-player.getSpaceship().get_capacity_crew() * (double)pow(.95, player.getSpaceship().get_ship_index()) * ((double(80) + rand() % 41) / 100.0) * 0.05);

        if (abs(fuelLoss) > curFuel) {
            fuelLoss = curFuel;
        }
        if (abs(crewLoss) > curCrew) {
            crewLoss = curCrew;
        }

        player.setSpaceship(calcuFuel(player.getSpaceship(), fuelLoss));
        player.setSpaceship(calcuCrew(player.getSpaceship(), crewLoss));

        cout << failure_d << endl;
        cout << "- " << abs(fuelLoss) << " fuel." << endl;
        cout << "- " << abs(crewLoss) << " crewmates." << endl;
    }
    cout << endl;

    cout << "Fuel / Crew / Progress Bar:" << endl;
    progressBar(player.getSpaceship().get_current_fuel(), player.getSpaceship().get_capacity_fuel());
    progressBar(player.getSpaceship().get_current_crew(), player.getSpaceship().get_capacity_crew());
    progressBar(pCur, pMax);

    cout << "||                                                          ||" << endl;
    outputContBuffer();
}

double gameRewards(Game& player, Planet selectedPlanet) {
    cout << setprecision(2);
    double baseReward = 10 * pow(2, selectedPlanet.get_hostility());

    string pSize = selectedPlanet.get_size();
    double bonusHostility = pow(1.21, selectedPlanet.get_hostility());
    double bonusPSize = selectedPlanet.get_sizeMult();

    string element1 = selectedPlanet.getElementName1();
    string element2 = selectedPlanet.getElementName2();
    string element3 = selectedPlanet.getElementName3();
    double elementMult1 = selectedPlanet.getElementMult1();
    double elementMult2 = selectedPlanet.getElementMult2();
    double elementMult3 = selectedPlanet.getElementMult3();

    // double bonusSTBase2 = player.getSpaceship().get_capacity_fuel() / 100;
    // double bonusShipPower = logBase(2, bonusSTBase2) + 1;
    double bonusShipType = pow(1.1, player.getSpaceship().get_ship_index());

    double bonusCrewmates = 1 + (player.getSpaceship().get_current_crew() / 10.0);
    double bonusOdysseys = 1 + log((double)player.getNumOdysseys() / 10 + 1);

    double totalMultiplier = bonusHostility * bonusPSize * bonusShipType * bonusCrewmates * bonusOdysseys;
    double cashEarned = baseReward * totalMultiplier;
    cout << "Rewards from planet " << selectedPlanet.get_name() << ":" << endl
         << "            Base reward: " << baseReward << " cash" << endl << endl

         << "        Hostility bonus: x" << bonusHostility << endl
         << "      Planet size bonus: x" << bonusPSize << " - " << pSize << endl
         << "         Elements bonus: x" << elementMult1 << " - " << element1 << endl
         << "                         x" << elementMult2 << " - " << element2 << endl
         << "                         x" << elementMult3 << " - " << element3 << endl << endl

         << "        Ship type bonus: x" << bonusShipType << endl
         << "        Crewmates bonus: x" << bonusCrewmates << endl
         << "Odysseys explored bonus: x" << bonusOdysseys << " - (" << player.getNumOdysseys() << ")" << endl << endl

         << "       Total multiplier: x" << totalMultiplier << endl << endl;

    outputContBuffer();
    
    player.setNumOdysseys(player.getNumOdysseys() + 1);

    return cashEarned;
}

void gameOver(Game& player, string planet_name, bool& failState) {
    if (player.getSpaceship().get_current_fuel() == 0 && player.getSpaceship().get_current_crew() == 0) {
        cout << "|| Game over. You ran out of fuel and crewmates.            ||" << endl;
    }

    else if (player.getSpaceship().get_current_fuel() == 0) {
        cout << "|| Game over. You ran out of fuel.                          ||" << endl;
        }

    else if (player.getSpaceship().get_current_crew() == 0) {
        cout << "|| Game over. You ran out of crewmates.                     ||" << endl;
    }
    cout << endl;
    cout << "Your spaceship has crashed and you are stranded on " << planet_name << "." << endl;
    cout << "Please buy a new spaceship or start a new game if out of money." << endl;
    cout << endl;

    player.setSpaceship(Spaceship("None", 0, 0, 0, 0));
    failState = true;

    outputBuffer();
}

int main() {
    srand(time(0));

    string filename;
    bool loaded;
    Game player;
    char input;
    bool calcFuel = false;
    bool calcCrew = false;
    bool calcCash = false;

    do {
        cout << "--------------------------------------------------------------" << endl
             << "-o-                                                        -o-" << endl
             << "--                                              --------    --" << endl
             << "-                        ----------        -----------       -" << endl
             << "-                     - *           -   --      ----         -" << endl
             << "-                    -         o      -        ---           -" << endl
             << "-                   -    *             -     ---             -" << endl
             << "-                  -             *      -  ---               -" << endl
             << "-                  -       o          *  --                  -" << endl
             << "-                  -   *         *     --                    -" << endl
             << "-                 --                 -- -                    -" << endl
             << "-               --  -  o   *     ---   -                     -" << endl
             << "-            ---     -     -----  o   -                      -" << endl
             << "-          ----     -------   o     -                        -" << endl
             << "-        -----------       --------                          -" << endl
             << "-      --------                                              -" << endl
             << "--    ----                                                  --" << endl
             << "-o-||       Planetary Odyssey - press 'P' to play.       ||-o-" << endl
             << "--------------------------------------------------------------" << endl;

        cin >> input;
    } while (input != 'P');

    // loads in-game ship data
    Spaceship ships[9];
    spaceshipData(ships);
    // loads in-game planet data
    int num_planets = 10;
    PlanetList planet_list(num_planets);
    planet_list.planetAdd(Planet());
    planet_list.planetAdd(Planet("Saturn", "A medium-sized, yellow, and gaseous planet composed of hydrogen, helium, and carbon." , 100, 2, "medium-sized"));
    // loads in-game event data
    ExplorationEvent mEvent;
    ExplorationEvent sEvent;
    uEventData(mEvent, sEvent);
    RandomEvent event;

    // loads autosave progress upon passing the start screen
    loaded = true;
    filename = "autosave.txt";
    load(filename, player, loaded);
    if (player.getFirstRun() == false) {
        cout << "--------------------------------------------------------------" << endl;
        cout << "Loading autosave progress:" << endl << endl;
        if (loaded == true) {
            player.printStats();
        }
        else {
            cout << "Error: Autosave was not able to be loaded." << endl;
        }
    }
    else {
        player.setFirstRun(false);
    }


    string userMenuOption;
    string userExploreOption;
    int user11Option; // explore -> explore
    string user11XOption; // explore -> explore -> planet
    string userExploreDiscoverOption;
    string user131Option; // explore -> discover -> yes
    int user14Option; // explore -> remove
    string user14XOption; // explore -> remove -> planet
    string userExploreStatsOption;
    string userShopOption;
    int userShopSpaceshipOption;
    string userShopChoice;
    string userPlayerInfoOption;

    bool failState = false;

    do {
        cout << "--------------------------------------------------------------" << endl
             << "|| Main Menu - please make your choice.                     ||" << endl
             << "   (1) - Explore                                              " << endl
             << "   (2) - Shop                                                 " << endl
             << "   (3) - New Game                                             " << endl
             << "   (4) - Load                                                 " << endl
             << "   (5) - Save                                                 " << endl
             << "   (6) - Player Progress                                      " << endl
             << "   (7) - Exit                                                 " << endl
             << "--------------------------------------------------------------" << endl;
        
        cin >> userMenuOption;

        if (userMenuOption == "1") { // Explore

            do {
                if (failState) {
                    failState = false;
                    break;
                }

                if (!hasSpaceship(player)) { // checks if player has spaceship before entering the explore loop
                    break;
                }

                else if (!hasFuel(player)) {
                    break;
                }
                
                else if (!hasCrew(player)) {
                    break;
                }

                cout << "--------------------------------------------------------------" << endl
                     << "|| Explore Menu - please make your choice.                  ||" << endl
                     << "   (1) - Select a Planet to Explore                           " << endl
                     << "   (2) - View Planets                                         " << endl
                     << "   (3) - Discover a Planet                                    " << endl
                     << "   (4) - Remove a Planet                                      " << endl
                     << "   (5) - Player Progress                                      " << endl
                     << "   (6) - Exit                                                 " << endl
                     << "--------------------------------------------------------------" << endl;
                
                cin >> userExploreOption;

                if (userExploreOption == "1") { // Select a Planet to Explore (MAIN GAME)

                    int i = 0;
                    do {
                        cout << "--------------------------------------------------------------" << endl;
                        printFuelCrewProgressBar(player);
                        cout << "--------------------------------------------------------------" << endl;

                        cout << "|| Choose a planet to embark towards:                       ||" << endl;
                        for (i = 0; i < planet_list.getNumPlanets(); i++) {
                            cout << "   (" << i + 1 << ") - " << planet_list.getPlanetName(i) << endl;
                        }

                        cout << "   (" << i + 1 << ") - " << "Exit" << endl;
                        cout << "--------------------------------------------------------------" << endl;

                        cin >> user11Option;

                        if (!cin) {
                            cout << "--------------------------------------------------------------" << endl;
                            cout << "|| Error - please enter an integer.                         ||" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            outputBuffer();
                        }

                        if (user11Option > 0 && user11Option <= planet_list.getNumPlanets()) {
                            Planet selectedPlanet;
                            do {
                                cout << "--------------------------------------------------------------" << endl;
                                cout << "You have selected: "  << endl << endl;
                                planet_list.printPlanetInfo(user11Option - 1);

                                selectedPlanet = planet_list.getPlanet(user11Option - 1);

                                cout << "|| Would you like to embark?                                ||" << endl;
                                cout << "   (1) - Yes                                                  " << endl;
                                cout << "   (2) - No - return to the planet select menu.               " << endl;
                                cout << "--------------------------------------------------------------" << endl;

                                cin >> user11XOption;

                            } while (user11XOption != "1" && user11XOption != "2");

                            if (user11XOption == "1") {

                                double luckFactor;
                                double progress;
                                double progress_cur = 0.00;
                                double progress_max = 100.00 * pow(2, selectedPlanet.get_hostility() - 1);
                                bool inOrbit = false;

                                cout << setprecision(2);

                                do {
                                    // buffers main game screen by one input
                                    if (inOrbit == false) {
                                        cout << "--------------------------------------------------------------" << endl;
                                        cout << "| Current planet: " << selectedPlanet.get_name() << endl;
                                        cout << "| Hostility: " << selectedPlanet.get_hostility() << endl << endl;                                        
                                        inOrbit = true;                                       
                                        cout << endl << endl << endl << endl;

                                        cout << "Fuel / Crew / Progress Bar:" << endl;
                                        progressBar(player.getSpaceship().get_current_fuel(), player.getSpaceship().get_capacity_fuel());
                                        progressBar(player.getSpaceship().get_current_crew(), player.getSpaceship().get_capacity_crew());
                                        progressBar(progress_cur, progress_max);
                                        cout << "||                                                          ||" << endl;   
                                        outputContBuffer();      
                                    }
                                    else if (Proc(25, 100)) {
                                        EventCalc(player, selectedPlanet, progress_cur, progress_max, mEvent, sEvent);
                                    }
                                    cout << "--------------------------------------------------------------" << endl;
                                    cout << "| Current planet: " << selectedPlanet.get_name() << endl;
                                    cout << "| Hostility: " << selectedPlanet.get_hostility() << endl << endl;

                                    luckFactor = (rand() % 101);
                                    cout << setprecision(0);
                                    cout << "You rolled a(n) " << luckFactor << "." << endl;

                                    progress = (player.getSpaceship().get_capacity_fuel() / 12.5) * luckFactor / 100;
                                    progress_cur += progress;
                                    cout << setprecision(2);
                                    cout << "Distance traveled: " << progress << " light-years" << endl;
                                    if (progress_cur >= progress_max) {
                                        cout << "(Overexplored by " << (progress_cur / progress_max) * 100 - 100 << "%). " << endl;
                                    }
                                    else {
                                        cout << endl;
                                    }




                                    printCalculations(player.getSpaceship(), calcFuel, calcCrew, calcCash, player.getCash());
                                    cout << endl;
                                    double fuelLost = -player.getSpaceship().get_capacity_fuel() * (double)pow(.95, player.getSpaceship().get_ship_index()) * ((double(80) + rand() % 41) / 100.0) * 0.01;
                                    player.setSpaceship(calcuFuel(player.getSpaceship(), fuelLost)); // increments fuel by (0.95)^ship_index * (0.8 to 1.2)*(1)% every loop

                                    cout << "Fuel / Crew / Progress Bar:" << endl;
                                    progressBar(player.getSpaceship().get_current_fuel(), player.getSpaceship().get_capacity_fuel());
                                    progressBar(player.getSpaceship().get_current_crew(), player.getSpaceship().get_capacity_crew());
                                    progressBar(progress_cur, progress_max);

                                    if (progress_cur < progress_max) {
                                        cout << "||                                                          ||" << endl;
                                        progressBuffer();
                                    }
                                    else {
                                        cout << "|| Congratulations! Your exploration of the planet is done. ||" << endl;
            

                                        outputContBuffer();

                                        progress_cur = progress_max;
                                    }

                                } while ((player.getSpaceship().get_current_fuel() > 0) && (player.getSpaceship().get_current_crew() > 0) && (progress_cur < progress_max));
                                    // Game over screen

                                cout << "--------------------------------------------------------------" << endl;
                                if (progress_cur >= progress_max) {

                                    if (selectedPlanet.get_name() != "Mars" && selectedPlanet.get_name() != "Saturn") {
                                        bool success;
                                        string tempName = planet_list.getPlanetName(user11Option - 1);
                                        success = planet_list.planetRemove(user11Option - 1);

                                        if (success) {
                                            cout << tempName << " has been removed from the GPS." << endl;
                                            cout << "You now have " << planet_list.getNumPlanets() << "/" << planet_list.getMaxPlanets() << " occupied planet slots." << endl;
                                        }
                                        else {
                                            cout << "Planet was not able to be removed." << endl;
                                        }  
                                        cout << endl;
                                        outputContBuffer(); 
                                    }
                                    double cashEarned = gameRewards(player, selectedPlanet);

                                    cout << "--------------------------------------------------------------" << endl;
                                    cout <<  "Total cash earned from this expedition: " << endl
                                         << cashEarned << " cash" << endl << endl;
                                    player.setCash(calculateCash(player, cashEarned, calcCash));
                                    printCalculations(player.getSpaceship(), calcFuel, calcCrew, calcCash, player.getCash());
                                    cout << endl;
                                    outputBuffer();

                                }
            
                                else {
                                    gameOver(player, selectedPlanet.get_name(), failState); // removes
                                    if (!failState) {
                                        if (selectedPlanet.get_name() != "Mars" && selectedPlanet.get_name() != "Saturn") {
                                            bool success;
                                            string tempName = planet_list.getPlanetName(user11Option - 1);
                                            success = planet_list.planetRemove(user11Option - 1);

                                            if (success) {
                                                cout << "--------------------------------------------------------------" << endl;
                                                cout << tempName << " has been removed from the GPS." << endl;
                                                cout << "You now have " << planet_list.getNumPlanets() << "/" << planet_list.getMaxPlanets() << " occupied planet slots." << endl;
                                            }
                                            else {
                                                cout << "Planet was not able to be removed." << endl;
                                            }   
                                        }     
                                    }           

                                    break; // potential bug
                                }
                                          
                            }

                        }

                    } while (user11Option != i + 1);
                }

                else if (userExploreOption == "2") { // View Planets
                    // View Planets
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "List of Planets (" << planet_list.getNumPlanets() << "/" <<  planet_list.getMaxPlanets() << "): " << endl << endl;
                    planet_list.printPlanetList();
                    
                    outputBuffer();
                }

                else if (userExploreOption == "3") { // Discover a Planet
                    // Discover a Planet
                    do {
                        cout << "--------------------------------------------------------------" << endl;
                        cout << "|| Are you sure you would like to discover a new planet?    ||" << endl;
                        cout << "|| Cost: 100 cash (Planets do not save upon reload.)        ||" << endl;
                        cout << "   (1) - Yes                                                  " << endl;
                        cout << "   (2) - No - back to the explore menu                        " << endl;
                        cout << "--------------------------------------------------------------" << endl;

                        cin >> userExploreDiscoverOption;

                        if (userExploreDiscoverOption == "1") {

                            if (!hasEnoughCash(player, 100)) {
                                break;
                            }

                            if (planet_list.getNumPlanets() < planet_list.getMaxPlanets()) {
                                do {
                                bool addState;
                                Planet tempPlanet = createRandomPlanet(player);

                                cout << "--------------------------------------------------------------" << endl;
                                tempPlanet.printInfo();
                                cout << endl;
                                
                                player.setCash(calculateCash(player, (-100), calcCash));
                                printCalculations(player.getSpaceship(), calcFuel, calcCrew, calcCash, player.getCash());
                                cout << endl;

                                cout << "|| You have discovered a planet. Would you like to add this ||" << endl;
                                cout << "|| planet to your GPS?                                      ||" << endl;
                                cout << "   (1) - Yes                                                  " << endl;
                                cout << "   (2) - No - back to the explore menu                        " << endl;
                                cout << "--------------------------------------------------------------" << endl;

                                cin >> user131Option;

                                if (user131Option == "1") {
                                    bool addState = planet_list.planetAdd(tempPlanet);
                                    if (addState) {
                                        cout << "--------------------------------------------------------------" << endl;
                                        cout << planet_list.getPlanetName(planet_list.getNumPlanets() - 1) << " has been added to the GPS." << endl;
                                    }

                                    outputBuffer();
                                }

                                } while (user131Option != "1" && user131Option != "2");
                            }
                            else {
                                cout << "--------------------------------------------------------------" << endl;
                                cout << "Error: you cannot have more than 10 planets." << endl;

                                outputBuffer();
                            }

                        }
                        

                    } while ((userExploreDiscoverOption != "1") && (userExploreDiscoverOption != "2"));
                }

                else if (userExploreOption == "4") { // Remove a Planet
                    // Remove a planet
                    int i;
    
                    if (planet_list.getNumPlanets() <= 2) {
                        cout << "--------------------------------------------------------------" << endl;
                        cout << "You have not discovered any planets this session!" << endl;

                        outputBuffer();

                    }
                    else {
                        do {
                        cout << "--------------------------------------------------------------" << endl;
                        cout << "|| Which planet would you like to delete from the GPS?      ||" << endl;
                        cout << "|| Note: you can only delete manually discovered planets.   ||" << endl;

                        for (i = 2; i < planet_list.getNumPlanets(); i++) {
                            cout << "   (" << i - 1 << ") - ";
                            planet_list.printPlanetName(i);
                            cout << endl;
                        }

                        cout << "   (" << i - 1 << ") - " << "Exit" << endl;
                        cout << "--------------------------------------------------------------" << endl;

                        cin >> user14Option;

                        if (!cin) {
                            cout << "--------------------------------------------------------------" << endl;
                            cout << "|| Error - please enter an integer.                         ||" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            outputBuffer();
                        }
                        else if (user14Option > 0 && user14Option < planet_list.getNumPlanets() - 1) {
                            do {
                                cout << "--------------------------------------------------------------" << endl;
                                cout << "Are you sure you want to remove ";
                                planet_list.printPlanetName(user14Option + 1);
                                cout << "?" << endl << endl;

                                planet_list.printPlanetInfo(user14Option + 1);

                                cout << "   (1) - Yes" << endl;
                                cout << "   (2) - No - back to deletion screen." << endl;
                                cout << "--------------------------------------------------------------" << endl;

                                cin >> user14XOption;
                            } while (user14XOption != "1" && user14XOption != "2");

                            if (user14XOption == "1") {
                                bool success;
                                string tempName = planet_list.getPlanetName(user14Option);
                                success = planet_list.planetRemove(user14Option);

                                if (success) {
                                    cout << "--------------------------------------------------------------" << endl;
                                    cout << "Success. " << tempName << " has been removed from the GPS." << endl;
                                    cout << "You now have " << planet_list.getNumPlanets() << "/" << planet_list.getMaxPlanets() << " occupied planet slots." << endl;
                                }
                                else {
                                    cout << "Planet was not able to be removed." << endl;
                                }

                                outputBuffer();
                            }
                        }
        
                        } while (user14Option != i - 1);
                    }


                }

                else if (userExploreOption == "5") { // Player Progress (Explore Menu)
                // displays current player and spaceship stats
                    printAllStats(player);
                    outputBuffer();
                }


            } while (userExploreOption != "6"); // Exit (Explore Menu)
        }

        else if (userMenuOption == "2") { // Shop
            //opens up the shop menu
            do {
                if (player.getSpaceship().get_ship_name() != "None") {
                cout << "--------------------------------------------------------------" << endl;
                printFuelCrewProgressBar(player);
                }

                cout << "--------------------------------------------------------------" << endl
                     << "|| Shop - please make your choice.                     Cost ||" << endl
                     << "   (1) - Spaceships                                           " << endl
                     << "   (2) - Buy Fuel                                  1 per unit " << endl
                     << "   (3) - Buy Crewmates                            10 per unit " << endl
                     << "   (4) - Sell Spaceship                                       " << endl
                     << "   (5) - Sell Fuel                               0.5 per unit " << endl
                     << "   (6) - Sell Crewmates                            5 per unit " << endl
                     << "   (7) - Player Progress                                      " << endl
                     << "   (8) - Exit                                                 " << endl
                     << "--------------------------------------------------------------" << endl;
                
                cin >> userShopOption;

                if (userShopOption == "1") { // Spaceships
    
                    do {
                        // add custom spaceship option 9 and move exit to option 10 if time permits
                        cout << "--------------------------------------------------------------" << endl
                             << "|| Spaceship Shop - please make your choice.           Cost ||" << endl
                             << "   (1) - Copper                                         100   " << endl
                             << "   (2) - Iron                                          1000   " << endl
                             << "   (3) - Bronze                                        4000   " << endl
                             << "   (4) - Silver                                       16000   " << endl
                             << "   (5) - Gold                                         64000   " << endl
                             << "   (6) - Platinum                                    256000   " << endl
                             << "   (7) - Diamond                                    1024000   " << endl
                             << "   (8) - Galactic Incarnate I                       4096000   " << endl
                             << "   (9) - Galactic Incarnate (Custom Tier)          variable   " << endl
                             << "   (10) - Exit                                                " << endl
                             << "--------------------------------------------------------------" << endl;
                        
                        cin >> userShopSpaceshipOption;

                        // (can't compare options using < or > because the options are of type string, using option of type integers would cause IL if the user were to enter a string)
                        if (!cin) {
                        cout << "--------------------------------------------------------------" << endl;
                        cout << "|| Error - please enter an integer.                         ||" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        outputBuffer();
                        }
                        else if (userShopSpaceshipOption > 0 && userShopSpaceshipOption < 9) {
                            int shipIndex = userShopSpaceshipOption - 1;

                            do {
                                
                                cout << "--------------------------------------------------------------" << endl;
                                ships[shipIndex].printInfos();
                                cout << endl
                                    << "You have the selected the " << ships[shipIndex].get_ship_name() << " Spaceship." << endl
                                    << "Would you like to buy this spaceship for " << ships[shipIndex].get_ship_cost() << " cash?" << endl
                                    << "   (1) - Yes" << endl
                                    << "   (2) - No" << endl
                                    << "--------------------------------------------------------------" << endl;
                                
                                cin >> userShopChoice;

                                if (userShopChoice == "1") {
                                    cout << "--------------------------------------------------------------" << endl;
                                    if (player.getCash() < ships[shipIndex].get_ship_cost()) {
                                        cout << "Insufficient funds! You need " << ships[shipIndex].get_ship_cost() - player.getCash()
                                             << " more cash." << endl;
                                    }
                                    else if (player.getSpaceship().get_ship_name() != "None") {
                                        cout << "Please sell your current spaceship before buying a new one." << endl;
                                    }
                                    else {
                                        player.setCash(player.getCash() - ships[shipIndex].get_ship_cost());
                                        player.setSpaceship(ships[shipIndex]);
                                        cout << "Purchase successful." << endl;
                                        cout << "You now have " << player.getCash() << " cash after the purchase." << endl;
                                    }
                                    cout << endl;
                                    outputBuffer();    
                                }

                            } while (userShopChoice != "1" && userShopChoice != "2");

                        }

                        else if (userShopSpaceshipOption == 9) {
                            int userGIOption;
                            int shipIndex;

                            do {
                                cout << "--------------------------------------------------------------" << endl;
                                cout << "|| Enter the tier value of a Galactic Incarnate Supership   ||" << endl;
                                cout << "|| you wish to buy (1 < x < 501):                           ||" << endl;
                                cout << "--------------------------------------------------------------" << endl;

                                cin >> userGIOption;
                                if (!cin) {
                                    cout << "--------------------------------------------------------------" << endl;
                                    cout << "|| Error - please enter an integer.                         ||" << endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    outputBuffer();
                                }
                                else if (userGIOption < 2 || userGIOption > 500) {
                                    cout << "--------------------------------------------------------------" << endl;
                                    cout << "|| Error - please enter a value with bounds 1 < x < 501.    ||" << endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    outputBuffer();                                    
                                }
                                else {
                                    Spaceship tempShip = calculateGalacticIncarnateShip(userGIOption);

                                    cout << "--------------------------------------------------------------" << endl;
                                    tempShip.printInfos();
                                    cout << endl;
                                    cout << " You have the selected the " << tempShip.get_ship_name() << " Spaceship." << endl
                                         << " Would you like to buy this spaceship for " << tempShip.get_ship_cost() << " cash?" << endl
                                         << "   (1) - Yes" << endl
                                         << "   (2) - No" << endl
                                         << "--------------------------------------------------------------" << endl;
                                    
                                    cin >> userShopChoice;

                                    if (userShopChoice == "1") {
                                        cout << "--------------------------------------------------------------" << endl;
                                        if (player.getCash() < tempShip.get_ship_cost()) {
                                            cout << "Insufficient funds! You need " << tempShip.get_ship_cost() - player.getCash()
                                                << " more cash." << endl;
                                        }
                                        else if (player.getSpaceship().get_ship_name() != "None") {
                                            cout << "Please sell your current spaceship before buying a new one." << endl;
                                        }
                                        else {
                                            player.setCash(player.getCash() - tempShip.get_ship_cost());
                                            player.setSpaceship(tempShip);
                                            cout << "Purchase successful." << endl;
                                            cout << "You now have " << player.getCash() << " cash after the purchase." << endl;
                                        }
                                        cout << endl;
                                        outputBuffer();    
                                    }
                                }

                                } while (userShopChoice != "1" && userShopChoice != "2");                        
                            }

                    } while (userShopSpaceshipOption != 10);

                }

                else if (userShopOption == "2") { // Buy Fuel
                    
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "|| How many units of fuel would you like to                 ||" << endl
                         << "|| supply to your spaceship?                                ||" << endl
                         << "--------------------------------------------------------------" << endl;
                    
                    int fShop;

                    cin >> fShop;
                    cout << "--------------------------------------------------------------" << endl;
                    if (!cin) {
                        cout << "|| Error - please enter an integer.                         ||" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else if (player.getSpaceship().get_ship_name() == "None") {
                        cout << "You do not currently have a spaceship!" << endl;
                    }
                    else if (fShop > (player.getSpaceship().get_capacity_fuel() - player.getSpaceship().get_current_fuel())) {
                        cout << "There is not enough storage on the spaceship!" << endl;
                    }
                    else if (fShop <= 0) {
                        cout << "You cannot supply the spaceship with negative or zero fuel!" << endl;
                    }
                    else {
                        player.setSpaceship(calculateFuel(player.getSpaceship(), fShop, calcFuel));
                        player.setCash(calculateCash(player, (0 - fShop), calcCash));
                        cout << endl;
                        printCalculations(player.getSpaceship(), calcFuel, calcCrew, calcCash, player.getCash());
                        cout << endl << "Fuel: " << endl;
                        progressBar(player.getSpaceship().get_current_fuel(), player.getSpaceship().get_capacity_fuel());
                        cout << endl;
                    }
                    outputBuffer();
                }

                else if (userShopOption == "3") { // Buy Crewmates
                   
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "|| How many many crewmates would you like to                ||" << endl
                         << "|| dedicate to your spaceship?                              ||" << endl
                         << "--------------------------------------------------------------" << endl;
                    
                    int cShop;

                    cin >> cShop;
                    cout << "--------------------------------------------------------------" << endl;
                    if (!cin) {
                        cout << "|| Error - please enter an integer.                         ||" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else if (player.getSpaceship().get_ship_name() == "None") {
                        cout << "You do not currently have a spaceship!" << endl;
                    }
                    else if (cShop > (player.getSpaceship().get_capacity_crew() - player.getSpaceship().get_current_crew())) {
                        cout << "There are not enough seats on the spaceship!" << endl;
                    }
                    else if (cShop <= 0) {
                        cout << "You cannot supply the spaceship with zero or negative crewmates!" << endl;
                    }
                    else {
                        player.setSpaceship(calculateCrew(player.getSpaceship(), cShop, calcCrew));
                        player.setCash(calculateCash(player, (0 - (cShop * 10)), calcCash));
                        cout << endl;
                        printCalculations(player.getSpaceship(), calcFuel, calcCrew, calcCash, player.getCash());
                        cout << endl << "Crewmates: " << endl;
                        progressBar(player.getSpaceship().get_current_crew(), player.getSpaceship().get_capacity_crew());
                        cout << endl;
                    }
                    outputBuffer();
                }

                else if (userShopOption == "4") { // Sell Spaceship
                    
                    cout << "--------------------------------------------------------------" << endl;
                    if (player.getSpaceship().get_ship_name() == "None") {
                        cout << "You do not have a spaceship to sell!" << endl;
                        outputBuffer();
                    }
                    else {
                        do {
                            player.getSpaceship().printInfos();
                            cout << endl 
                                 << "|| Are you sure you would like to sell your spaceship       ||" << endl
                                 << "|| and its contents?                                        ||" << endl
                                 << "   (1) - Yes" << endl
                                 << "   (2) - No" << endl
                                 << "--------------------------------------------------------------" << endl;
                            
                            cin >> userShopChoice;

                            if (userShopChoice == "1") {

                                cout << "--------------------------------------------------------------" << endl;
                                double cashReturned = sellShip(player.getSpaceship());
                                cout << endl << "You sold your " << player.getSpaceship().get_ship_name() << " Spaceship and its" << endl
                                     << "contents for " << cashReturned << " cash." << endl;
                                player.setSpaceship(Spaceship("None", 0, 0, 0, 0));
                                player.setCash(player.getCash() + cashReturned);
                                cout << "You now have " << player.getCash() << " cash." << endl;
                                outputBuffer();
                            }
                        } while (userShopChoice != "1" && userShopChoice != "2");
                    }
                }

                else if (userShopOption == "5") { // Sell Fuel

                    cout << "--------------------------------------------------------------" << endl;
                    cout << "|| How many units of fuel would you like to                 ||" << endl
                         << "|| sell from your spaceship?                                ||" << endl
                         << "--------------------------------------------------------------" << endl;
                    
                    int fShop;

                    cin >> fShop;
                    cout << "--------------------------------------------------------------" << endl;
                    if (!cin) {
                        cout << "|| Error - please enter an integer.                         ||" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else if (fShop <= 0) {
                        cout << "You cannot sell negative or zero fuel!" << endl;
                    }                    
                    else if (fShop > player.getSpaceship().get_current_fuel()) {
                        cout << "There is not enough fuel from the spaceship!" << endl;
                    }
                    else {
                        player.setSpaceship(calculateFuel(player.getSpaceship(), -fShop, calcFuel));
                        player.setCash(calculateCash(player, fShop * 0.5, calcCash));
                        cout << endl;
                        printCalculations(player.getSpaceship(), calcFuel, calcCrew, calcCash, player.getCash());
                        cout << endl << "Fuel: " << endl;
                        progressBar(player.getSpaceship().get_current_fuel(), player.getSpaceship().get_capacity_fuel());
                        cout << endl;
                    }
                    outputBuffer();
                }

                else if (userShopOption == "6") { // Sell Crewmates

                    cout << "--------------------------------------------------------------" << endl;
                    cout << "|| How many many crewmates would you like to                ||" << endl
                         << "|| retire from your spaceship?                              ||" << endl
                         << "--------------------------------------------------------------" << endl;
                    
                    int cShop;

                    cin >> cShop;
                    cout << "--------------------------------------------------------------" << endl;
                    if (!cin) {
                        cout << "|| Error - please enter an integer.                         ||" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else if (cShop <= 0) {
                        cout << "You cannot sell zero or negative crewmates!" << endl;
                    }                    
                    else if (cShop > player.getSpaceship().get_current_crew()) {
                        cout << "There are not enough crewmates to be sold from the spaceship!" << endl;
                    }
                    else {
                        player.setSpaceship(calculateCrew(player.getSpaceship(), -cShop, calcCrew));
                        player.setCash(calculateCash(player, (cShop * 5), calcCash));
                        cout << endl;
                        printCalculations(player.getSpaceship(), calcFuel, calcCrew, calcCash, player.getCash());
                        cout << endl << "Crewmates: " << endl;
                        progressBar(player.getSpaceship().get_current_crew(), player.getSpaceship().get_capacity_crew());
                        cout << endl;
                    }
                    outputBuffer();
                }

                else if (userShopOption == "7") {
                    printAllStats(player);

                    outputBuffer();
                }

            } while (userShopOption != "8"); // Exit (Shop Menu)
        }

        else if (userMenuOption == "3") { // New Game
            // New Game
            cout << "--------------------------------------------------------------" << endl
                 << "|| Enter a file name to create a new save:                  ||" << endl
                 << "|| (Press '1' to cancel and return to the main menu.)       ||" << endl
                 << "--------------------------------------------------------------" << endl;
            
            cin >> filename;
            if (filename != "1") {
                Game tempPlayer;

                save(filename, tempPlayer);
                load(filename, player, loaded);

                cout << "--------------------------------------------------------------" << endl;
                player.printStats();
                cout << endl;
                cout << "New save file has been created.                               " << endl;

                outputBuffer();
            }
        }

        else if (userMenuOption == "4") { // Load
            cout << "--------------------------------------------------------------" << endl
                 << "|| Enter a file name to load your previous save:            ||" << endl
                 << "--------------------------------------------------------------" << endl;

            cin >> filename;
            loaded = true;
            load(filename, player, loaded);
            if (loaded == true) {
                cout << "--------------------------------------------------------------" << endl;
                player.printStats();
                cout << endl << "Save loaded." << endl;
            }
            outputBuffer();
        }

        else if (userMenuOption == "5") { // Save

            cout << "--------------------------------------------------------------" << endl
                 << "|| Enter a file name to save your current progress:         ||" << endl
                 << "--------------------------------------------------------------" << endl;

            cin >> filename;

            save(filename, player);
            cout << "--------------------------------------------------------------" << endl;
            player.printStats();
            cout << endl << "Progress has been saved." << endl;
            outputBuffer();
        }

        else if (userMenuOption == "6") { // Player Progress (from Main Menu)
            printAllStats(player);

            outputBuffer();
        }

        else if (userMenuOption == "8") { // Test
            cout << "--------------------------------------------------------------" << endl;
            cout << "Testing: " << endl;
            Planet temporary = createRandomPlanet(player);
            temporary.printInfo();
            cout << "Size multiplier: " << temporary.get_sizeMult() << endl;
            sEvent.set_planet_location("Saturn");
            cout << sEvent.get_planet_location() << endl;
            cout << sEvent.get_event_multiplier() << endl;
            cout << sEvent.get_success_rate() << endl;
            cout << sEvent.get_description() << endl;
        }

    } while (userMenuOption != "7"); // Program termination

    // Autosave mechanic once program terminates
    cout << "--------------------------------------------------------------" << endl;
    cout << "Autosaving progress before terminating:" << endl << endl;
    filename = "autosave.txt";

    player.setFirstRun(false);
    save(filename, player);

    player.printStats();
    cout << endl << "Done." << endl;

    cout << "--------------------------------------------------------------" << endl;
    planet_list.deletePlanetList();
    cout << "|| Program is terminated.                                   ||" << endl;

    return 0;
}
