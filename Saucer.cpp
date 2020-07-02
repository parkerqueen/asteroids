/*
 * Saucer.cpp
 *
 *  Created on: May 3, 2018
 *      Author: parkerqueen
 */

#include "Saucer.h"

// Constructor
Saucer::Saucer(int rad) : Entity(rad, 8) { constructGeometry(); }

// Constructs the geomtery of the saucer
void Saucer::constructGeometry() {
    geometry = new Point[vertices];
    float dtheta = 360 / (vertices - 2), theta = 0;
    for (short i = 0; i < vertices; ++i) {
        int sub =
            (i != 0 && i != 5) ? radius * ((i == 2 || i == 3) ? 0.25 : 0.5) : 0;
        geometry[i][0] = position[0] + (radius - sub) * cos(Deg2Rad(theta));
        geometry[i][1] = position[1] + (radius - sub) * sin(Deg2Rad(theta));
        theta +=
            dtheta / ((i != 1 && i != 2 && i != 3) ? 1 : ((i == 2) ? 2 : 4));
    }
}

// Returns the reward points of the Saucer
int Saucer::reward() const {
    if (radius == SCR_SMALL) return 500;
    return 100;
}

// Triggers the saucer's gun and its bombs
void Saucer::triggerGun(Point dir) {
    if (!gun.trigger()) gun.load(dir, position, SCR_BMB);
}

// Draws a saucer
void Saucer::draw() {
    for (short i = 0; i < vertices - 1; ++i)
        DrawLine(geometry[i][0], geometry[i][1], geometry[i + 1][0],
                 geometry[i + 1][1], 2, colors[RED]);
    DrawLine(geometry[vertices - 1][0], geometry[vertices - 1][1],
             geometry[0][0], geometry[0][1], 2, colors[RED]);
    DrawLine(geometry[1][0], geometry[1][1], geometry[4][0], geometry[4][1], 2,
             colors[RED]);
    DrawLine(geometry[0][0], geometry[0][1], geometry[5][0], geometry[5][1], 2,
             colors[RED]);
}

// Returns the type of Saucer
int Saucer::type() const { return SCR; }

// Returns the gun of Saucer
Gun& Saucer::getGun() { return gun; }

// Destructor
Saucer::~Saucer() {}
