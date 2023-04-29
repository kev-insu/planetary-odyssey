#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cmath>

#include "Spaceship.h"
#include "Planet.h"
#include "PlanetList.h"
#include "Game.h"


using namespace std;

void load(string filename, Game& player, bool& loaded) { // loads save data from a specified file
    ifstream inStream(filename);
    if (!inStream.is_open()) {
        loaded = false;
    }
    else {
        int temp_int;
        string temp_string;
        bool temp_bool;
        Spaceship tempShip;

        inStream >> temp_int;
        player.setCash(temp_int);
        inStream >> temp_int;
        player.setNumOdysseys(temp_int);
        inStream.ignore();
        getline(inStream, temp_string);
        tempShip.set_ship_name(temp_string);
        inStream >> temp_int;  
        tempShip.set_ship_value(temp_int);   
        inStream >> temp_int;
        tempShip.set_capacity_fuel(temp_int);
        inStream >> temp_int;
        tempShip.set_capacity_crew(temp_int);
        inStream >> temp_int;
        tempShip.set_current_fuel(temp_int);
        inStream >> temp_int;
        tempShip.set_current_crew(temp_int);
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

    outStream << player.getCash() << endl;
    outStream << player.getNumOdysseys() << endl;

    Spaceship tempShip = player.getSpaceship();

    outStream << tempShip.get_ship_name() << endl;
    outStream << tempShip.get_ship_value() << endl;
    outStream << tempShip.get_capacity_fuel() << endl;
    outStream << tempShip.get_capacity_crew() << endl;
    outStream << tempShip.get_current_fuel() << endl;
    outStream << tempShip.get_current_crew() << endl;

    outStream << player.getFirstRun() << endl;

    outStream.close();
}

void spaceshipData(Spaceship ships[]) { // contains all data from purchasable spaceships
    ships[1] = Spaceship("Iron", 1000, 200, 22);
    ships[2] = Spaceship("Bronze", 4000, 400, 33);
    ships[3] = Spaceship("Silver", 16000, 800, 50);
    ships[4] = Spaceship("Gold", 64000, 1600, 75);
    ships[5] = Spaceship("Platinum", 256000, 3200, 113);
    ships[6] = Spaceship("Diamond", 1024000, 6400, 170);
    ships[7] = Spaceship("Galactic Incarnate", 4096000, 12800, 250);
}

int sellShip(Spaceship ship) { // calculates ship value from selling
    int cashReturned = 0;
    cout << "Spaceship value: + " << ship.get_ship_value() << " cash" << endl;
    cashReturned += ship.get_ship_value();

    int fuelToCash = (ship.get_current_fuel() / 2);
    cout << "Fuel:            + " << fuelToCash << " cash" << endl;
    cashReturned += fuelToCash;

    cout << "Crewmates:       + " << ship.get_current_crew() * 5 << " cash" << endl;
    cashReturned += ship.get_current_crew() * 5;

    return cashReturned;
}

void progressBar(int cur, int max) { // creates a progress bar with 2 percent increments per character
    int percent = (cur * 100) / max;
    cout << "   [";

    if (percent > 100) {
        percent = 100;
    }

    for (int i = 0; i < (percent / 2); i++) {
        cout << "#";
    }
    for (int j = 0; j < (50 - (percent / 2)); j++) {
        cout << " ";
    }

    cout << "] " << ((cur * 100) / max) << "%" << endl;

    /*
    if (max >= 50) {
        int increment = max / 50;
        int num = cur / increment;
        int empty = 50 - num;
        cout << "[";
        for (int i = 0; i < num; i++) {
            cout << "#";
        }
        for (int j = 0; j < empty; j++) {
            cout << " ";
        }
        cout << "] " << ((cur * 100) / max) << "%" << endl;
    }
    */
}

Spaceship calculateFuel(Spaceship ship, int num, bool& calcFuel) { // adds or subtracts fuel
    int cur = ship.get_current_fuel();
    int calc = cur + num;
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
    calcCrew = true;

    return tempShip;
}

int calculateCash(Game player, int num, bool& calcCash) { // adds or subtracts cash
    int cur = player.getCash();
    int calc = cur + num;
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

void printCalculations(Spaceship ship, bool& calcFuel, bool& calcCrew, bool &calcCash, int cash) { // displays counts after calculations
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

Planet createRandomPlanet() { // creates a random planet; over 960 million combinations of unique planets by properties, (when paired with unique names, over 10 quadrillion combinations)
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
    int numSize = 10;
    int numColor = 12;
    int numType = 5;
    int numElement = 118;
    string planetSize[numSize] = {"dwarf", "miniscule", "small", "medium-sized", "large", "huge", "giant", "massive", "vast", "colossal"};
    string planetSizeVar[numSize] = {"Dwarf", "Miniscule", "Small", "Medium-sized", "Large", "Huge", "Giant", "Massive", "Vast", "Colossal"};
    string planetColor[numColor] = {"pink", "red", "yellow", "green", "blue", "purple", "white", "black", "lavender", "beige", "jade", "silver"};
    string planetType[numType] = {"gaseous", "terrestrial", "aquatic", "clear", "cloudy"};
    string planetElements[numElement] = {"hydrogen", "helium", "lithium", "beryllium", "boron", "carbon", "nitrogen", "oxygen", "flourine", "neon", "sodium", "magnesium", "alnuminum", 
    "silicon", "phosphorus", "sulfur", "chlorine", "argon", "potassium", "calcium", "scandium", "titanium", "vanadium", "chromium", "manganese", "iron", "cobalt", "nickel", "copper",
    "zinc", "gallium", "germanium", "arsenic", "selenium", "bromine", "krypton", "rubidium", "stronium", "yttrium", "zirconium", "niobium", "molybdenum", "technetium", "ruthenium",
    "rhodium", "palladium", "silver", "cadmium", "indium", "tin", "antimony", "tellurium", "iodine", "xenon", "caesium", "barium", "lathanum", "cerium", "praseodymium", "neodymium",
    "promethium", "samarium", "europium", "gadolinium", "terbium", "dysprosium", "holmium", "erbium", "thulium", "ytterbium", "lutetium", "fracnium", "radium", "actinium", "thorium",
    "protactinium", "uranium", "neptunium", "plutonium", "americium", "curium", "berkelium", "californium", "einsteinium", "fermium", "mendelevium", "nobelium", "lawrencium",
    "rutherfordium", "dubnium", "seaborgium", "bhorium", "hassium", "meitnerium", "darmstadtium", "roentgenium", "copernicium", "nihonium", "flerovium", "moscovium", "livermorium",
    "tennessine", "oganesson"};

    // selects elements
    int tempIndex;
    int indexFirstElement = (rand() % 103);

    tempIndex = rand() % 103;
    while (tempIndex == indexFirstElement) {
        tempIndex = rand() % 103;
    }
    int indexSecondElement = tempIndex;

    tempIndex = rand() % 103;
    while (tempIndex == indexFirstElement || tempIndex == indexSecondElement) {
        tempIndex = rand() % 103;
    }
    int indexThirdElement = tempIndex;

    string firstElement = planetElements[indexFirstElement];
    string secondElement = planetElements[indexSecondElement];
    string thirdElement = planetElements[indexThirdElement];

    int sizeIndex = rand() % numSize;
    string selectedSize = planetSize[sizeIndex];
    string varSize = planetSizeVar[sizeIndex];

    string selectedColor = planetColor[rand() % numColor];
    string selectedType = planetType[rand() % numType];

    // creates string of description
    string description = "A " + selectedSize + ", " + selectedColor + ", and " + selectedType + " planet composed of " + firstElement + ", " + secondElement + ", and " + thirdElement + ".";

    // random hostility
    int hostility = 1+ (rand() % 10);

    // random fuel_required
    int fuel_required;
    if (hostility == 1) {
        fuel_required = 50;
    }
    else {
        fuel_required = 100 * pow(2, hostility - 2);
    }

    Planet tempPlanet;
    tempPlanet.set_name(name);
    tempPlanet.set_description(description);
    tempPlanet.set_fuel_required(fuel_required);
    tempPlanet.set_hostility(hostility);
    tempPlanet.set_size(varSize);

    return tempPlanet;
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

void outputBuffer() {
    string buffer;
    cout << "|| Press any key to return.                                 ||" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cin >> buffer;
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
    planet_list.planetAdd(Planet("Saturn", "A colloquially beautiful planet whose rings permeate the essence of beauty." , 250, 2, "medium"));



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
    string user11Option; // explore -> explore
    string userExploreViewOption;
    string userExploreDiscoverOption;
    string user131Option; // explore -> discover -> yes
    int user14Option; // explore -> remove
    string user14XOption; // explore -> remove -> planet
    string userExploreStatsOption;
    string userShopOption;
    string userShopSpaceshipOption;
    string userShopChoice;
    string userPlayerInfoOption;

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

        if (userMenuOption == "1") {
            do {
                cout << "--------------------------------------------------------------" << endl
                     << "|| Explore Menu - please make your choice.                  ||" << endl
                     << "   (1) - Select a Planet to Explore                           " << endl
                     << "   (2) - View Planets                                         " << endl
                     << "   (3) - Discover a Planet                                    " << endl
                     << "   (4) - Remove a Planet                                     " << endl
                     << "   (5) - Player Progress                                      " << endl
                     << "   (6) - Exit                                                 " << endl
                     << "--------------------------------------------------------------" << endl;
                
                cin >> userExploreOption;

                if (userExploreOption == "1") {
                    cout << "|| Choose a planet to embark towards:                       ||" << endl;
                    int i = 0;
                    for (i = 0; i < planet_list.getNumPlanets; i++) {
                        cout << "   (" << i + 1 << ") - ";
                        planet_list.getPlanetName(i);
                        cout << endl;
                    }

                    cout << "   (" << i << ") - " << "Exit" << endl;
                    cout << "--------------------------------------------------------------" << endl;

                    cin >> user11Option;

                    if (!cin) {
                        cout << "--------------------------------------------------------------" << endl;
                        cout << "|| Error - please enter an integer.                         ||" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        outputBuffer();
                    }                    
                }

                else if (userExploreOption == "2") {
                    // View Planets
                    do {
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "List of Planets (" << planet_list.getNumPlanets() << "/" <<  planet_list.getMaxPlanets() << "): " << endl << endl;
                    planet_list.printPlanetList();
                    
                    cout << endl;
                    cout << "|| Press '1' to return to the explore menu.                 ||" << endl;
                    cout << "--------------------------------------------------------------" << endl;
                    cin >> userExploreViewOption;

                    } while (userExploreViewOption != "1");
                }

                else if (userExploreOption == "3") {
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
                            if (planet_list.getNumPlanets() < planet_list.getMaxPlanets()) {
                                do {
                                bool addState;
                                Planet tempPlanet = createRandomPlanet();

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

                else if (userExploreOption == "4") {
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

                else if (userExploreOption == "5") {
                // displays current player and spaceship stats
                do {
                    printAllStats(player);
                    cin >> userExploreStatsOption;

                } while (userExploreStatsOption != "1");
                }


            } while (userExploreOption != "6");
        }

        else if (userMenuOption == "2") {
            //opens up the shop menu
            do {
                cout << "--------------------------------------------------------------" << endl
                     << "|| Shop - please make your choice.                      Cost ||" << endl
                     << "   (1) - Spaceships                                           " << endl
                     << "   (2) - Buy Fuel                                  1 per unit " << endl
                     << "   (3) - Buy Crewmates                            10 per unit " << endl
                     << "   (4) - Sell Spaceship                                       " << endl
                     << "   (5) - Sell Fuel                0.5 per unit (rounded down) " << endl
                     << "   (6) - Sell Crewmates                            5 per unit " << endl
                     << "   (7) - Exit                                                 " << endl
                     << "--------------------------------------------------------------" << endl;
                
                cin >> userShopOption;

                if (userShopOption == "1") {
                    // Spaceships
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
                             << "   (8) - Galactic Incarnate                         4096000   " << endl
                             << "   (9) - Exit                                                 " << endl
                             << "--------------------------------------------------------------" << endl;
                        
                        cin >> userShopSpaceshipOption;

                        // (can't compare options using < or > because the options are of type string, using option of type integers would cause IL if the user were to enter a string)
                        string s = userShopSpaceshipOption;
                        if ((s == "1") || (s == "2") || (s == "3") || (s == "4") || (s == "5") || (s == "6") || (s == "7") || (s == "8")) {
                            int shipIndex = stoi(userShopSpaceshipOption) - 1;

                            do { 
                                cout << "--------------------------------------------------------------" << endl;
                                ships[shipIndex].printInfo();
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
                                }

                            } while (userShopChoice != "1" && userShopChoice != "2");
                            cout << endl;
                            outputBuffer();

                        }
                    } while (userShopSpaceshipOption != "9");

                }

                else if (userShopOption == "2") {
                    // Buy Fuel
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

                else if (userShopOption == "3") {
                    // Buy Crewmates
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

                else if (userShopOption == "4") {
                    // Sell Spaceship
                    cout << "--------------------------------------------------------------" << endl;
                    if (player.getSpaceship().get_ship_name() == "None") {
                        cout << "You do not have a spaceship to sell!" << endl;
                    }
                    else {
                        do {
                            player.getSpaceship().printInfo();
                            cout << endl 
                                 << "|| Are you sure you would like to sell your spaceship       ||" << endl
                                 << "|| and its contents?                                        ||" << endl
                                 << "   (1) - Yes" << endl
                                 << "   (2) - No" << endl
                                 << "--------------------------------------------------------------" << endl;
                            
                            cin >> userShopChoice;

                            if (userShopChoice == "1") {
                                cout << "--------------------------------------------------------------" << endl;
                                int cashReturned = sellShip(player.getSpaceship());
                                cout << endl << "You sold your " << player.getSpaceship().get_ship_name() << " " << endl
                                     << "and its contents for " << cashReturned << " cash." << endl;
                                player.setSpaceship(Spaceship("None", 0, 0, 0));
                                player.setCash(player.getCash() + cashReturned);
                                cout << "You now have " << player.getCash() << " cash." << endl;
                            }
                        } while (userShopChoice != "1" && userShopChoice != "2");
                    }
                    outputBuffer();
                }

                else if (userShopOption == "5") {
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

                else if (userShopOption == "6") {
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

            } while (userShopOption != "7");
        }
        else if (userMenuOption == "3") {
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
        else if (userMenuOption == "4") {
            // Load
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

        else if (userMenuOption == "5") {
            // Save
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

        else if (userMenuOption == "6") {
            // Player Progress (from Main Menu)
            printAllStats(player);

            outputBuffer();
        }

        else if (userMenuOption == "8") {
            cout << "--------------------------------------------------------------" << endl;
            cout << "Testing: " << endl;
            Planet temporary = createRandomPlanet();
            temporary.printInfo();
        }

    } while (userMenuOption != "7"); // Program termination

    // autosave mechanic once program terminates
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
