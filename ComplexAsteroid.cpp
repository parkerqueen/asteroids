/*
 * ComplexAsteroid.cpp
 *
 *  Created on: May 2, 2018
 *      Author: parkerqueen
 */

#include "ComplexAsteroid.h"

// Constructs a Complex Asteroid
ComplexAsteroid::ComplexAsteroid(int rad) : Asteroid(rad) { timer = 0; }

// Constructs a Complex Asteroid at given position
ComplexAsteroid::ComplexAsteroid(int rad, Point& pos) : Asteroid(rad, pos) {
    timer = 0;
}

// Moves the asteroid and changes direction if 3 seconds have passed
void ComplexAsteroid::move() {
    if (timer == 3000) {
        timer = 0;
        setDirection(Point());
    }
    Entity::move();
}

// Logs the time since last direction change
void ComplexAsteroid::dirTimer() { timer += 25; }

// Returns the type, CXA
int ComplexAsteroid::type() const { return CXA; }
