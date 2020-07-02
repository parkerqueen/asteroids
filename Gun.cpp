/*
 * Gun.cpp
 *
 *  Created on: May 5, 2018
 *      Author: parkerqueen
 */

#include "Gun.h"

// Constructor
Gun::Gun() {
    firedB = 0;
    firingRange = SCR_FRANG;
    numBombs = 0;
}

// Loads a new bomb into the array of given type and at given position &
// direction
void Gun::load(Point& dir, Point& pos, int btype) {
    ++numBombs;
    Bomb* temp = firedB;
    firedB = new Bomb[numBombs];
    for (short i = 0; i < numBombs - 1; ++i) firedB[i] = temp[i];
    Bomb newB = Bomb(dir, pos, btype);
    firedB[numBombs - 1] = newB;
    delete[] temp;
    Mix_PlayChannel(-1, fire, 0);
}

// Destroys a bomb with its ID
void Gun::destroyBomb(long bombId) {
    for (short i = 0; i < numBombs && bombId != -1; ++i)
        if (firedB[i].getId() == bombId) {
            --numBombs;
            Bomb* temp = firedB;
            firedB = new Bomb[numBombs];
            for (short j = 0, k = 0; j < numBombs + 1; ++j)
                if (i != j) {
                    firedB[k] = temp[j];
                    ++k;
                }
            delete[] temp;
            break;
        }
}

// Triggers all the bombs with some checks to destroy them
bool Gun::trigger() {
    long expired = -1;
    for (short i = 0; i < numBombs; ++i) {
        firedB[i].move();
        firedB[i].draw();
        if (firedB[i].distance() > firingRange) expired = firedB[i].getId();
    }
    destroyBomb(expired);
    return numBombs;
}

// Sets the bomb speed of a ship bomb
void Gun::bombspeed(float spd) { Bomb::setspeed(spd); }

// Returns the bombs array
Bomb* Gun::getFiredBombs() const { return firedB; }

// Returns total number of bombs
int Gun::getNumBombs() const { return numBombs; }

// Destructor
Gun::~Gun() { delete[] firedB; }
