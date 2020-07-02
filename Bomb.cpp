/*
 * Bomb.cpp
 *
 *  Created on: May 5, 2018
 *      Author: parkerqueen
 */

#include "Bomb.h"

int Bomb::shp_bspeed = 0;

// Constructs the bomb at given pos, with the given direction
Bomb::Bomb(Point dir, Point pos, int btype) : Entity(dir, pos, BOMB, btype) {
    firedDistance = 0;
    this->btype = btype;
}

// Moves the bomb
void Bomb::move() {
    int realSpeed = (btype == SHP_BMB) ? shp_bspeed : speed;
    position[0] += direct[0] * realSpeed;
    position[1] += direct[1] * realSpeed;
    wrapAround();
    firedDistance += sqrt((direct[0] * realSpeed) * (direct[0] * realSpeed) +
                          (direct[1] + realSpeed) * (direct[1] + realSpeed));
}

// Draws the bomb
void Bomb::draw() {
    DrawCircle(position[0], position[1], radius, colors[ORANGE]);
}

// Sets the staic bomb speed which is used to drive ship bombs
void Bomb::setspeed(float spd) { shp_bspeed = spd; }

// Gives the total distance covered by the bomb
float Bomb::distance() const { return firedDistance; }

// Returns the type of the bomb, ship bomb or saucer bomb
int Bomb::type() const { return btype; }
