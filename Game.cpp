#include <iostream>
#include <string>
using namespace std;

#include "Spaceship.h"
#include "Game.h"
Game::Game() {
    cash = 100;
    num_odysseys = 0;
    shipObject = Spaceship();
    firstRun = true;
}

Game::Game(int userCash, int userNumOdysseys, Spaceship userShip, bool userFirstRun) {
    cash = userCash;
    num_odysseys = userNumOdysseys;
    shipObject = userShip;
    firstRun = userFirstRun;
}

void Game::printStats() {
    cout << "Player Progress and Statistics:                               " << endl;
    cout << "   Cash: " << cash << endl;
    cout << "   Number of odysseys completed: " << num_odysseys << endl << endl;
    shipObject.printInfo();
}

int Game::getCash() {
    return cash;
}

int Game::getNumOdysseys() {
    return num_odysseys;
}

Spaceship Game::getSpaceship() {
    return shipObject;
}

bool Game::getFirstRun() {
    return firstRun;
}

void Game::setCash(int userCash) {
    cash = userCash;
}

void Game::setNumOdysseys(int userNumOdysseys) {
    num_odysseys = userNumOdysseys;
}

void Game::setSpaceship(Spaceship userShip) {
    shipObject = userShip;
}

void Game::setFirstRun(bool userFirstRun) {
    firstRun = userFirstRun;
}